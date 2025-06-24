#include "mcp_client.hpp"
#include <iostream>
#include <fstream>
#include <string>

using json = nlohmann::json;

void printUsage(const char* programName) {
    std::cout << "Usage: " << programName << " <api_key> [config_file]" << std::endl;
    std::cout << "  api_key     - Your Amap API key" << std::endl;
    std::cout << "  config_file - Optional config file path (default: config.json)" << std::endl;
    std::cout << std::endl;
    std::cout << "Example: " << programName << " your_api_key_here" << std::endl;
    std::cout << "Example: " << programName << " your_api_key_here custom_config.json" << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printUsage(argv[0]);
        return 1;
    }
    
    std::string apiKey = argv[1];
    std::string configPath = (argc > 2) ? argv[2] : "config.json";
    
    std::cout << "=== Amap MCP Client Example ===" << std::endl;
    std::cout << "API Key: " << apiKey.substr(0, 8) << "..." << std::endl;
    std::cout << "Config File: " << configPath << std::endl;
    std::cout << "===============================" << std::endl;
    
    // Create MCP client
    MCPClient client;
    
    // Step 1: Load configuration
    std::cout << "\n[Step 1] Loading configuration..." << std::endl;
    if (!client.loadConfig(configPath)) {
        std::cerr << "❌ Failed to load configuration from: " << configPath << std::endl;
        std::cerr << "   Make sure the config file exists and has the correct format." << std::endl;
        return 1;
    }
    std::cout << "✅ Configuration loaded successfully!" << std::endl;
    
    // Step 2: List available servers
    std::cout << "\n[Step 2] Available servers:" << std::endl;
    const auto& servers = client.getServers();
    if (servers.empty()) {
        std::cerr << "❌ No servers found in configuration" << std::endl;
        return 1;
    }
    
    for (const auto& [name, config] : servers) {
        std::cout << "   📍 " << name << " (" << config.command << ")" << std::endl;
        std::cout << "      Args: ";
        for (size_t i = 0; i < config.args.size(); ++i) {
            if (i > 0) std::cout << " ";
            std::cout << config.args[i];
        }
        std::cout << std::endl;
        std::cout << "      Env vars: " << config.env.size() << " variables" << std::endl;
    }
    
    // Step 3: Connect to amap-maps server
    std::cout << "\n[Step 3] Connecting to amap-maps server..." << std::endl;
    if (!client.connect("amap-maps")) {
        std::cerr << "❌ Failed to connect to amap-maps server" << std::endl;
        std::cerr << "   Make sure the server command is available and executable." << std::endl;
        return 1;
    }
    std::cout << "✅ Connected to amap-maps server successfully!" << std::endl;
    
    try {
        // Step 4: Initialize the connection
        std::cout << "\n[Step 4] Initializing MCP connection..." << std::endl;
        json initResult = client.initialize("Amap MCP Client", "1.0.0");
        
        if (initResult.contains("error")) {
            std::cerr << "❌ Initialization failed: " << initResult["error"]["message"] << std::endl;
            return 1;
        }
        
        std::cout << "✅ Initialization successful!" << std::endl;
        if (initResult.contains("result") && initResult["result"].contains("serverInfo")) {
            auto serverInfo = initResult["result"]["serverInfo"];
            std::cout << "   Server: " << serverInfo.value("name", "Unknown") << " v" 
                      << serverInfo.value("version", "Unknown") << std::endl;
        }
        
        // Step 5: List available tools
        std::cout << "\n[Step 5] Listing available tools..." << std::endl;
        json toolsResult = client.listTools();
        
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
        
        // Step 6: List available resources
        std::cout << "\n[Step 6] Listing available resources..." << std::endl;
        json resourcesResult = client.listResources("mcp://amap-maps/");
        
        if (resourcesResult.contains("error")) {
            std::cerr << "❌ Failed to list resources: " << resourcesResult["error"]["message"] << std::endl;
        } else {
            std::cout << "✅ Resources retrieved successfully!" << std::endl;
            if (resourcesResult.contains("result") && resourcesResult["result"].contains("resources")) {
                auto resources = resourcesResult["result"]["resources"];
                std::cout << "   Found " << resources.size() << " resources:" << std::endl;
                for (const auto& resource : resources) {
                    std::cout << "   📄 " << resource.value("uri", "Unknown") 
                              << " - " << resource.value("name", "No name") << std::endl;
                }
            }
        }
        
        // Step 7: Set log level
        std::cout << "\n[Step 7] Setting log level..." << std::endl;
        json logResult = client.setLogLevel("info");
        
        if (logResult.contains("error")) {
            std::cerr << "❌ Failed to set log level: " << logResult["error"]["message"] << std::endl;
        } else {
            std::cout << "✅ Log level set to 'info' successfully!" << std::endl;
        }
        
        // Step 8: Call a tool (geocoding example)
        std::cout << "\n[Step 8] Calling geocoding tool..." << std::endl;
        json toolArgs = {
            {"address", "北京市朝阳区"},
            {"city", "北京"}
        };
        
        json callResult = client.callTool("geocoding", toolArgs);
        
        if (callResult.contains("error")) {
            std::cerr << "❌ Tool call failed: " << callResult["error"]["message"] << std::endl;
        } else {
            std::cout << "✅ Tool call successful!" << std::endl;
            if (callResult.contains("result")) {
                std::cout << "   Result: " << callResult["result"].dump(2) << std::endl;
            }
        }
        
        // Step 9: Read a resource (status example)
        std::cout << "\n[Step 9] Reading resource status..." << std::endl;
        json readResult = client.readResource("mcp://amap-maps/status");
        
        if (readResult.contains("error")) {
            std::cerr << "❌ Failed to read resource: " << readResult["error"]["message"] << std::endl;
        } else {
            std::cout << "✅ Resource read successfully!" << std::endl;
            if (readResult.contains("result")) {
                std::cout << "   Content: " << readResult["result"].dump(2) << std::endl;
            }
        }
        
        // Step 10: Test with different geocoding parameters
        std::cout << "\n[Step 10] Testing different geocoding parameters..." << std::endl;
        
        // Test 1: Geocoding with different address
        json testArgs1 = {
            {"address", "上海市浦东新区"},
            {"city", "上海"}
        };
        
        json testResult1 = client.callTool("geocoding", testArgs1);
        if (!testResult1.contains("error")) {
            std::cout << "✅ Shanghai geocoding successful!" << std::endl;
        } else {
            std::cout << "❌ Shanghai geocoding failed: " << testResult1["error"]["message"] << std::endl;
        }
        
        // Test 2: Geocoding with coordinates
        json testArgs2 = {
            {"location", "116.397428,39.90923"},
            {"radius", "1000"}
        };
        
        json testResult2 = client.callTool("geocoding", testArgs2);
        if (!testResult2.contains("error")) {
            std::cout << "✅ Coordinate geocoding successful!" << std::endl;
        } else {
            std::cout << "❌ Coordinate geocoding failed: " << testResult2["error"]["message"] << std::endl;
        }
        
    } catch (const std::exception& e) {
        std::cerr << "❌ Error during MCP operations: " << e.what() << std::endl;
        return 1;
    }
    
    // Step 11: Disconnect
    std::cout << "\n[Step 11] Disconnecting from server..." << std::endl;
    client.disconnect();
    std::cout << "✅ Disconnected successfully!" << std::endl;
    
    std::cout << "\n🎉 Amap MCP client example completed successfully!" << std::endl;
    std::cout << "   All operations were performed using the MCP protocol." << std::endl;
    std::cout << "   The client successfully communicated with the amap-maps server." << std::endl;
    
    return 0;
} 