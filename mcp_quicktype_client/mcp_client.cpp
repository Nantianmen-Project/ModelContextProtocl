#include "mcp_client.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>
#include <chrono>
#include <cstring>

#ifdef _WIN32
#include <windows.h>
#include <process.h>
#else
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#endif

MCPClient::MCPClient() : process_id(0), is_connected(false) {}

MCPClient::~MCPClient() {
    disconnect();
}

bool MCPClient::loadConfig(const std::string& configPath) {
    try {
        std::ifstream file(configPath);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open config file: " << configPath << std::endl;
            return false;
        }
        
        nlohmann::json config;
        file >> config;
        
        if (!config.contains("mcpServers") || !config["mcpServers"].is_object()) {
            std::cerr << "Error: Invalid config format - missing mcpServers object" << std::endl;
            return false;
        }
        
        servers.clear();
        for (auto& [name, serverConfig] : config["mcpServers"].items()) {
            MCPServerConfig server;
            
            if (serverConfig.contains("command")) {
                server.command = serverConfig["command"];
            }
            
            if (serverConfig.contains("args") && serverConfig["args"].is_array()) {
                for (const auto& arg : serverConfig["args"]) {
                    server.args.push_back(arg);
                }
            }
            
            if (serverConfig.contains("env") && serverConfig["env"].is_object()) {
                for (auto& [key, value] : serverConfig["env"].items()) {
                    server.env[key] = value;
                }
            }
            
            servers[name] = server;
        }
        
        std::cout << "Loaded " << servers.size() << " server configurations" << std::endl;
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Error loading config: " << e.what() << std::endl;
        return false;
    }
}

bool MCPClient::connect(const std::string& serverName) {
    if (is_connected) {
        disconnect();
    }
    
    auto it = servers.find(serverName);
    if (it == servers.end()) {
        std::cerr << "Error: Server '" << serverName << "' not found in config" << std::endl;
        return false;
    }
    
    const MCPServerConfig& config = it->second;
    
#ifdef _WIN32
    // Windows implementation
    SECURITY_ATTRIBUTES sa;
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.bInheritHandle = TRUE;
    sa.lpSecurityDescriptor = NULL;
    
    HANDLE hChildStdoutRd, hChildStdoutWr;
    HANDLE hChildStdinRd, hChildStdinWr;
    
    if (!CreatePipe(&hChildStdoutRd, &hChildStdoutWr, &sa, 0) ||
        !CreatePipe(&hChildStdinRd, &hChildStdinWr, &sa, 0)) {
        std::cerr << "Error creating pipes" << std::endl;
        return false;
    }
    
    SetHandleInformation(hChildStdoutRd, HANDLE_FLAG_INHERIT, 0);
    SetHandleInformation(hChildStdinWr, HANDLE_FLAG_INHERIT, 0);
    
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    si.hStdError = hChildStdoutWr;
    si.hStdOutput = hChildStdoutWr;
    si.hStdInput = hChildStdinRd;
    si.dwFlags |= STARTF_USESTDHANDLES;
    ZeroMemory(&pi, sizeof(pi));
    
    // Build command line
    std::string cmdLine = config.command;
    for (const auto& arg : config.args) {
        cmdLine += " " + arg;
    }
    
    // Build environment
    std::string envStr;
    for (const auto& [key, value] : config.env) {
        envStr += key + "=" + value + "\0";
    }
    envStr += "\0";
    
    if (!CreateProcess(NULL, const_cast<char*>(cmdLine.c_str()), NULL, NULL, TRUE, 0,
                      const_cast<char*>(envStr.c_str()), NULL, &si, &pi)) {
        std::cerr << "Error creating process" << std::endl;
        return false;
    }
    
    process_id = pi.dwProcessId;
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    CloseHandle(hChildStdoutWr);
    CloseHandle(hChildStdinRd);
    
    // Store handles for communication
    stdin_pipe = hChildStdinWr;
    stdout_pipe = hChildStdoutRd;
    
#else
    // Unix implementation
    int stdout_pipe_fd[2];
    int stdin_pipe_fd[2];
    
    if (pipe(stdout_pipe_fd) == -1 || pipe(stdin_pipe_fd) == -1) {
        std::cerr << "Error creating pipes" << std::endl;
        return false;
    }
    
    pid_t pid = fork();
    if (pid == -1) {
        std::cerr << "Error forking process" << std::endl;
        return false;
    }
    
    if (pid == 0) {
        // Child process
        close(stdout_pipe_fd[0]);
        close(stdin_pipe_fd[1]);
        
        dup2(stdout_pipe_fd[1], STDOUT_FILENO);
        dup2(stdin_pipe_fd[0], STDIN_FILENO);
        
        close(stdout_pipe_fd[1]);
        close(stdin_pipe_fd[0]);
        
        // Set environment variables
        for (const auto& [key, value] : config.env) {
            setenv(key.c_str(), value.c_str(), 1);
        }
        
        // Build argv
        std::vector<char*> argv;
        argv.push_back(const_cast<char*>(config.command.c_str()));
        for (const auto& arg : config.args) {
            argv.push_back(const_cast<char*>(arg.c_str()));
        }
        argv.push_back(nullptr);
        
        execvp(config.command.c_str(), argv.data());
        std::cerr << "Error executing command: " << config.command << std::endl;
        exit(1);
    } else {
        // Parent process
        close(stdout_pipe_fd[1]);
        close(stdin_pipe_fd[0]);
        
        process_id = pid;
        stdin_pipe = stdin_pipe_fd[1];
        stdout_pipe = stdout_pipe_fd[0];
    }
#endif
    
    is_connected = true;
    std::cout << "Connected to server: " << serverName << std::endl;
    return true;
}

void MCPClient::disconnect() {
    if (!is_connected) return;
    
#ifdef _WIN32
    if (process_id > 0) {
        HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, process_id);
        if (hProcess) {
            TerminateProcess(hProcess, 0);
            CloseHandle(hProcess);
        }
        CloseHandle(stdin_pipe);
        CloseHandle(stdout_pipe);
    }
#else
    if (process_id > 0) {
        kill(process_id, SIGTERM);
        waitpid(process_id, nullptr, 0);
        close(stdin_pipe);
        close(stdout_pipe);
    }
#endif
    
    process_id = 0;
    is_connected = false;
    std::cout << "Disconnected from server" << std::endl;
}

std::string MCPClient::sendRequest(const nlohmann::json& request) {
    if (!is_connected) {
        throw std::runtime_error("Not connected to server");
    }
    
    std::string requestStr = request.dump() + "\n";
    
#ifdef _WIN32
    DWORD bytesWritten;
    if (!WriteFile(stdin_pipe, requestStr.c_str(), requestStr.length(), &bytesWritten, NULL)) {
        throw std::runtime_error("Failed to write to server");
    }
#else
    ssize_t bytesWritten = write(stdin_pipe, requestStr.c_str(), requestStr.length());
    if (bytesWritten == -1) {
        throw std::runtime_error("Failed to write to server");
    }
#endif
    
    // Read response
    std::string response;
    char buffer[4096];
    
#ifdef _WIN32
    DWORD bytesRead;
    while (ReadFile(stdout_pipe, buffer, sizeof(buffer) - 1, &bytesRead, NULL) && bytesRead > 0) {
        buffer[bytesRead] = '\0';
        response += buffer;
        if (response.find('\n') != std::string::npos) {
            break;
        }
    }
#else
    ssize_t bytesRead;
    while ((bytesRead = read(stdout_pipe, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytesRead] = '\0';
        response += buffer;
        if (response.find('\n') != std::string::npos) {
            break;
        }
    }
#endif
    
    return response;
}

nlohmann::json MCPClient::initialize(const std::string& clientName, const std::string& clientVersion) {
    nlohmann::json request = {
        {"jsonrpc", "2.0"},
        {"id", 1},
        {"method", "initialize"},
        {"params", {
            {"protocolVersion", "2024-11-05"},
            {"capabilities", {
                {"roots", {
                    {"listChanged", true}
                }},
                {"sampling", {
                    {"additionalProperties", true}
                }},
                {"experimental", {
                    {"additionalProperties", true}
                }}
            }},
            {"clientInfo", {
                {"name", clientName},
                {"version", clientVersion}
            }}
        }}
    };
    
    std::string response = sendRequest(request);
    return nlohmann::json::parse(response);
}

nlohmann::json MCPClient::listTools() {
    nlohmann::json request = {
        {"jsonrpc", "2.0"},
        {"id", 2},
        {"method", "tools/list"}
    };
    
    std::string response = sendRequest(request);
    return nlohmann::json::parse(response);
}

nlohmann::json MCPClient::callTool(const std::string& toolName, const nlohmann::json& arguments) {
    nlohmann::json request = {
        {"jsonrpc", "2.0"},
        {"id", 3},
        {"method", "tools/call"},
        {"params", {
            {"name", toolName},
            {"arguments", arguments}
        }}
    };
    
    std::string response = sendRequest(request);
    return nlohmann::json::parse(response);
}

nlohmann::json MCPClient::listResources(const std::string& uri) {
    nlohmann::json request = {
        {"jsonrpc", "2.0"},
        {"id", 4},
        {"method", "resources/list"},
        {"params", {
            {"uri", uri}
        }}
    };
    
    std::string response = sendRequest(request);
    return nlohmann::json::parse(response);
}

nlohmann::json MCPClient::readResource(const std::string& uri) {
    nlohmann::json request = {
        {"jsonrpc", "2.0"},
        {"id", 5},
        {"method", "resources/read"},
        {"params", {
            {"uri", uri}
        }}
    };
    
    std::string response = sendRequest(request);
    return nlohmann::json::parse(response);
}

nlohmann::json MCPClient::setLogLevel(const std::string& level) {
    nlohmann::json request = {
        {"jsonrpc", "2.0"},
        {"id", 6},
        {"method", "logging/setLevel"},
        {"params", {
            {"level", level}
        }}
    };
    
    std::string response = sendRequest(request);
    return nlohmann::json::parse(response);
}

bool MCPClient::isConnected() const {
    return is_connected;
}

const std::map<std::string, MCPServerConfig>& MCPClient::getServers() const {
    return servers;
} 