#include <iostream>
#include <memory>
#include <string>
#include <grpcpp/grpcpp.h>
#include "../pb/mcp_service.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using mcp::MCPService;
using mcp::RegisterRequest;
using mcp::RegisterResponse;
using mcp::InitializeRequest;
using mcp::InitializeResult;
using mcp::JSONRPCRequest;
using mcp::JSONRPCResponse;
using mcp::ClientCapabilities;
using mcp::ServerCapabilities;
using mcp::Implementation;

class MCPClient {
public:
    MCPClient(std::shared_ptr<Channel> channel)
        : stub_(MCPService::NewStub(channel)) {}

    bool Register() {
        mcp::RegisterRequest request;
        mcp::RegisterResponse response;
        ClientContext context;

        // Set client capabilities
        auto* capabilities = request.mutable_capabilities();
        capabilities->mutable_experimental()->insert({"supports_file_operations", "true"});
        capabilities->mutable_experimental()->insert({"supports_sandbox", "true"});

        // Set client info
        auto* info = request.mutable_client_info();
        info->set_name("MCP Client");
        info->set_version("1.0.0");

        Status status = stub_->Register(&context, request, &response);
        if (status.ok()) {
            std::cout << "Registration successful. Session ID: " << response.session_id() << std::endl;
            return true;
        } else {
            std::cout << "Registration failed: " << status.error_message() << std::endl;
            return false;
        }
    }

    bool Initialize() {
        mcp::InitializeRequest request;
        mcp::InitializeResult response;
        ClientContext context;

        Status status = stub_->Initialize(&context, request, &response);
        if (status.ok()) {
            std::cout << "Initialization successful. Protocol version: " << response.protocol_version() << std::endl;
            return true;
        } else {
            std::cout << "Initialization failed: " << status.error_message() << std::endl;
            return false;
        }
    }

    bool CreateFile(const std::string& path, const std::string& content) {
        mcp::JSONRPCRequest request;
        mcp::JSONRPCResponse response;
        ClientContext context;

        request.set_method("createFile");
        request.mutable_params()->mutable_additional_params()->insert({"path", path});
        request.mutable_params()->mutable_additional_params()->insert({"content", content});

        Status status = stub_->HandleRequest(&context, request, &response);
        if (status.ok()) {
            const auto& result = response.result();
            const auto& additional_result = result.additional_result();
            if (additional_result.find("error_code") == additional_result.end()) {
                std::cout << "File created successfully: " << path << std::endl;
                return true;
            } else {
                std::cout << "Failed to create file: " << additional_result.at("error_message") << std::endl;
                return false;
            }
        } else {
            std::cout << "Failed to create file: " << status.error_message() << std::endl;
            return false;
        }
    }

    bool DeleteFile(const std::string& path) {
        mcp::JSONRPCRequest request;
        mcp::JSONRPCResponse response;
        ClientContext context;

        request.set_method("deleteFile");
        request.mutable_params()->mutable_additional_params()->insert({"path", path});

        Status status = stub_->HandleRequest(&context, request, &response);
        if (status.ok()) {
            const auto& result = response.result();
            const auto& additional_result = result.additional_result();
            if (additional_result.find("error_code") == additional_result.end()) {
                std::cout << "File deleted successfully: " << path << std::endl;
                return true;
            } else {
                std::cout << "Failed to delete file: " << additional_result.at("error_message") << std::endl;
                return false;
            }
        } else {
            std::cout << "Failed to delete file: " << status.error_message() << std::endl;
            return false;
        }
    }

    bool ReadFile(const std::string& path, std::string& content) {
        mcp::JSONRPCRequest request;
        mcp::JSONRPCResponse response;
        ClientContext context;

        request.set_method("readFile");
        request.mutable_params()->mutable_additional_params()->insert({"path", path});

        Status status = stub_->HandleRequest(&context, request, &response);
        if (status.ok()) {
            const auto& result = response.result();
            const auto& additional_result = result.additional_result();
            if (additional_result.find("error_code") == additional_result.end()) {
                content = additional_result.at("content");
                std::cout << "File read successfully: " << path << std::endl;
                return true;
            } else {
                std::cout << "Failed to read file: " << additional_result.at("error_message") << std::endl;
                return false;
            }
        } else {
            std::cout << "Failed to read file: " << status.error_message() << std::endl;
            return false;
        }
    }

    bool ListFiles(const std::string& path, std::vector<std::string>& files) {
        mcp::JSONRPCRequest request;
        mcp::JSONRPCResponse response;
        ClientContext context;

        request.set_method("listFiles");
        request.mutable_params()->mutable_additional_params()->insert({"path", path});

        Status status = stub_->HandleRequest(&context, request, &response);
        if (status.ok()) {
            const auto& result = response.result();
            const auto& additional_result = result.additional_result();
            if (additional_result.find("error_code") == additional_result.end()) {
                files.clear();
                std::string files_json = additional_result.at("files");
                // TODO: Parse JSON array of files
                std::cout << "Files listed successfully in: " << path << std::endl;
                std::cout << files_json << std::endl;
                return true;
            } else {
                std::cout << "Failed to list files: " << additional_result.at("error_message") << std::endl;
                return false;
            }
        } else {
            std::cout << "Failed to list files: " << status.error_message() << std::endl;
            return false;
        }
    }

private:
    std::unique_ptr<MCPService::Stub> stub_;
};

int main(int argc, char** argv) {
    std::string target_address("localhost:50051");
    MCPClient client(
        grpc::CreateChannel(target_address, grpc::InsecureChannelCredentials()));

    // Register and initialize
    if (!client.Register() || !client.Initialize()) {
        return 1;
    }

    // Test file operations
    std::string test_content = "Hello, World!";
    if (client.CreateFile("test.txt", test_content)) {
        std::string read_content;
        if (client.ReadFile("test.txt", read_content)) {
            std::cout << "Read content: " << read_content << std::endl;
        }

        std::vector<std::string> files;
        if (client.ListFiles(".", files)) {
            std::cout << "Files in current directory:" << std::endl;
            for (const auto& file : files) {
                std::cout << "- " << file << std::endl;
            }
        }

        client.DeleteFile("test.txt");
    }

    return 0;
} 