#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <chrono>
#include <grpcpp/grpcpp.h>
#include "../pb/mcp_service.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using mcp::MCPService;
using mcp::JSONRPCRequest;
using mcp::JSONRPCResponse;

class Host {
public:
    Host(std::shared_ptr<Channel> channel)
        : stub_(MCPService::NewStub(channel)) {}

    void SimulateExecution() {
        std::cout << "Starting execution simulation..." << std::endl;

        // Create a test file
        std::string test_content = "This is a test file created by the host.";
        if (SendCreateFileRequest("test.txt", test_content)) {
            std::this_thread::sleep_for(std::chrono::seconds(1));

            // List files
            if (SendListFilesRequest(".")) {
                std::this_thread::sleep_for(std::chrono::seconds(1));

                // Read the file
                if (SendReadFileRequest("test.txt")) {
                    std::this_thread::sleep_for(std::chrono::seconds(1));

                    // Delete the file
                    SendDeleteFileRequest("test.txt");
                }
            }
        }
    }

private:
    std::unique_ptr<MCPService::Stub> stub_;

    bool SendCreateFileRequest(const std::string& path, const std::string& content) {
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

    bool SendDeleteFileRequest(const std::string& path) {
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

    bool SendReadFileRequest(const std::string& path) {
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
                std::cout << "File read successfully: " << path << std::endl;
                std::cout << "Content: " << additional_result.at("content") << std::endl;
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

    bool SendListFilesRequest(const std::string& path) {
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
                std::cout << "Files listed successfully in: " << path << std::endl;
                std::cout << "Files:" << std::endl;
                std::string files_json = additional_result.at("files");
                // TODO: Parse JSON array of files
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
};

int main(int argc, char** argv) {
    std::string target_address("localhost:50051");
    Host host(
        grpc::CreateChannel(target_address, grpc::InsecureChannelCredentials()));

    host.SimulateExecution();
    return 0;
} 