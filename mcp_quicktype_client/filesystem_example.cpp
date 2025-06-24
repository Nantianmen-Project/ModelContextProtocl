#include "mcp_client.hpp"
#include <iostream>
#include <string>

using json = nlohmann::json;

void printUsage(const char* programName) {
    std::cout << "Usage: " << programName << " [config_file]" << std::endl;
    std::cout << "  config_file - Optional config file path (default: config.json)" << std::endl;
    std::cout << std::endl;
    std::cout << "Example: " << programName << std::endl;
    std::cout << "Example: " << programName << " custom_config.json" << std::endl;
}

int main(int argc, char* argv[]) {
    std::string configPath = "config.json";
    if (argc > 1) {
        configPath = argv[1];
    }

    std::cout << "=== MCP Filesystem Server Example ===" << std::endl;
    std::cout << "Config File: " << configPath << std::endl;
    std::cout << "===============================" << std::endl;

    MCPClient fsClient;
    std::cout << "\n[Step 1] Loading configuration..." << std::endl;
    if (!fsClient.loadConfig(configPath)) {
        std::cerr << "❌ Failed to load config for filesystem server" << std::endl;
        return 1;
    }
    if (!fsClient.connect("filesystem")) {
        std::cerr << "❌ Failed to connect to filesystem server" << std::endl;
        return 1;
    }
    json fsInit = fsClient.initialize("Filesystem Example", "1.0.0");
    if (fsInit.contains("error")) {
        std::cerr << "❌ Filesystem server initialization failed: " << fsInit["error"]["message"] << std::endl;
        return 1;
    }
    std::cout << "✅ Filesystem server initialized!" << std::endl;

    // Step 2: List available tools
    std::cout << "\n[Step 2] Listing available tools..." << std::endl;
    json toolsResult = fsClient.listTools();
    if (toolsResult.contains("error")) {
        std::cerr << "❌ Failed to list tools: " << toolsResult["error"]["message"] << std::endl;
    } else {
        std::cout << "✅ Tools retrieved successfully!" << std::endl;
        if (toolsResult.contains("result") && toolsResult["result"].contains("tools")) {
            auto tools = toolsResult["result"]["tools"];
            std::cout << "   Found " << tools.size() << " tools:" << std::endl;
            for (const auto& tool : tools) {
                std::cout << "   🔧 " << tool.value("name", "Unknown")
                          << " - " << tool.value("description", "No description") << std::endl;
            }
        }
    }

    // Step 3: List directory in root
    std::cout << "\n[Step 3] Listing directory in root..." << std::endl;
    json listArgs = { {"path", "."} };
    json listResult = fsClient.callTool("list_directory", listArgs);
    if (listResult.contains("error")) {
        std::cerr << "❌ Failed to list directory: " << listResult["error"]["message"] << std::endl;
    } else {
        std::cout << "✅ Directory listed successfully!" << std::endl;
        if (listResult.contains("result") && listResult["result"].contains("content")) {
            for (const auto& entry : listResult["result"]["content"]) {
                if (entry.contains("text")) {
                    std::cout << entry["text"] << std::endl;
                }
            }
        } else {
            std::cout << listResult.dump(2) << std::endl;
        }
    }

    // 判断是否成功的lambda
    auto isSuccess = [](const json& result) {
        if (result.contains("error")) return false;
        if (result.contains("result") && result["result"].contains("isError") && result["result"]["isError"]) return false;
        return true;
    };

    // Step 4: Create a new file
    std::cout << "\n[Step 4] Creating a new file..." << std::endl;
    std::string path = "test_file.txt";
    std::string content = "Hello, MCP Filesystem!\nThis is a test file.\n";
    json createArgs = {
        {"path", path},
        {"content", content}
    };
    json createResult = fsClient.callTool("write_file", createArgs);
    if (isSuccess(createResult)) {
        std::cout << "✅ File created successfully!" << std::endl;
    } else {
        std::cerr << "❌ Failed to create file: " << createResult.dump(2) << std::endl;
    }

    // Step 5: Read the file
    std::cout << "\n[Step 5] Reading the file..." << std::endl;
    json readArgs = {
        {"path", path}
    };
    json readResult = fsClient.callTool("read_file", readArgs);
    if (isSuccess(readResult)) {
        std::cout << "✅ File read successfully!" << std::endl;
        if (readResult.contains("content")) {
            std::cout << "   Content: " << readResult["content"] << std::endl;
        }
    } else {
        std::cerr << "❌ Failed to read file: " << readResult.dump(2) << std::endl;
    }

    // Step 6: Delete the file (move to .deleted)
    std::cout << "\n[Step 6] Deleting the file (move to .deleted)..." << std::endl;
    json moveArgs = {
        {"source", path},
        {"destination", path + ".deleted"}
    };
    json moveResult = fsClient.callTool("move_file", moveArgs);
    if (isSuccess(moveResult)) {
        std::cout << "✅ File deleted (moved to .deleted) successfully!" << std::endl;
    } else {
        std::cerr << "❌ Failed to delete file: " << moveResult.dump(2) << std::endl;
    }

    fsClient.disconnect();
    std::cout << "\n🎉 Filesystem server example completed!" << std::endl;
    return 0;
} 