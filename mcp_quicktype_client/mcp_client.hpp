#pragma once

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <nlohmann/json.hpp>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

struct MCPServerConfig {
    std::string command;
    std::vector<std::string> args;
    std::map<std::string, std::string> env;
};

class MCPClient {
public:
    MCPClient();
    ~MCPClient();

    // Configuration
    bool loadConfig(const std::string& configPath);
    
    // Connection management
    bool connect(const std::string& serverName);
    void disconnect();
    bool isConnected() const;
    
    // MCP operations
    nlohmann::json initialize(const std::string& clientName, const std::string& clientVersion);
    nlohmann::json listTools();
    nlohmann::json callTool(const std::string& toolName, const nlohmann::json& arguments);
    nlohmann::json listResources(const std::string& uri);
    nlohmann::json readResource(const std::string& uri);
    nlohmann::json setLogLevel(const std::string& level);
    
    // Utility
    const std::map<std::string, MCPServerConfig>& getServers() const;

private:
    std::string sendRequest(const nlohmann::json& request);
    
    std::map<std::string, MCPServerConfig> servers;
    
#ifdef _WIN32
    HANDLE stdin_pipe;
    HANDLE stdout_pipe;
    DWORD process_id;
#else
    int stdin_pipe;
    int stdout_pipe;
    pid_t process_id;
#endif
    
    bool is_connected;
}; 