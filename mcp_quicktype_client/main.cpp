#include "mcp_client.hpp"
#include <iostream>
#include <fstream>

using json = nlohmann::json;

int main(int argc, char* argv[]) {
    std::string configPath = "config.json";
    
    if (argc > 1) {
        configPath = argv[1];
    }
    
    MCPClient client;
    
    // Load configuration
    std::cout << "Loading configuration from: " << configPath << std::endl;
    if (!client.loadConfig(configPath)) {
        std::cerr << "Failed to load configuration" << std::endl;
        return 1;
    }
    
    // List available servers
    std::cout << "\nAvailable servers:" << std::endl;
    for (const auto& [name, config] : client.getServers()) {
        std::cout << "  - " << name << " (" << config.command << ")" << std::endl;
    }
    
    // Connect to amap-maps server
    std::cout << "\nConnecting to amap-maps server..." << std::endl;
    if (!client.connect("amap-maps")) {
        std::cerr << "Failed to connect to amap-maps server" << std::endl;
        return 1;
    }
    
    try {
        // Initialize the connection
        std::cout << "\nInitializing connection..." << std::endl;
        json initResult = client.initialize("MCP QuickType Client", "1.0.0");
        std::cout << "Initialization result: " << initResult.dump(2) << std::endl;
        
        // List available tools
        std::cout << "\nListing available tools..." << std::endl;
        json toolsResult = client.listTools();
        std::cout << "Tools result: " << toolsResult.dump(2) << std::endl;
        
        // List resources
        std::cout << "\nListing resources..." << std::endl;
        json resourcesResult = client.listResources("mcp://amap-maps/");
        std::cout << "Resources result: " << resourcesResult.dump(2) << std::endl;
        
        // Set log level
        std::cout << "\nSetting log level..." << std::endl;
        json logResult = client.setLogLevel("info");
        std::cout << "Log level result: " << logResult.dump(2) << std::endl;
        
        // Call a tool (example with geocoding)
        std::cout << "\nCalling geocoding tool..." << std::endl;
        json toolArgs = {
            {"address", "北京市朝阳区"},
            {"city", "北京"}
        };
        json callResult = client.callTool("geocoding", toolArgs);
        std::cout << "Tool call result: " << callResult.dump(2) << std::endl;
        
        // Read a resource (example)
        std::cout << "\nReading resource..." << std::endl;
        json readResult = client.readResource("mcp://amap-maps/status");
        std::cout << "Read resource result: " << readResult.dump(2) << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error during MCP operations: " << e.what() << std::endl;
    }
    
    // Disconnect
    std::cout << "\nDisconnecting..." << std::endl;
    client.disconnect();
    
    std::cout << "MCP client example completed successfully!" << std::endl;
    return 0;
} 