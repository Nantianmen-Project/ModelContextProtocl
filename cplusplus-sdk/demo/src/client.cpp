#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>
#include "mcp_service.grpc.pb.h"

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
using mcp::JSONRPCNotification;
using mcp::Empty;
using mcp::JSONRPCBatchRequest;
using mcp::JSONRPCBatchResponse;
using mcp::RegisterInputSchemaRequest;
using mcp::RegisterInputSchemaResponse;
using mcp::GetInputSchemaRequest;
using mcp::InputSchema;
using mcp::ListResourcesRequest;
using mcp::ListResourcesResult;
using mcp::ReadResourceRequest;
using mcp::ReadResourceResult;
using mcp::RegisterToolRequest;
using mcp::RegisterToolResponse;
using mcp::ListToolsRequest;
using mcp::ListToolsResponse;
using mcp::RegisterPromptRequest;
using mcp::RegisterPromptResponse;
using mcp::GetPromptRequest;
using mcp::Prompt;
using mcp::ListPromptsRequest;
using mcp::ListPromptsResponse;
using mcp::UpdatePromptRequest;
using mcp::UpdatePromptResponse;
using mcp::DeletePromptRequest;
using mcp::DeletePromptResponse;

class MCPClient {
public:
    MCPClient(std::shared_ptr<Channel> channel)
        : stub_(MCPService::NewStub(channel)) {}

    bool Register(const std::string& client_id) {
        RegisterRequest request;
        request.set_client_id(client_id);

        RegisterResponse response;
        ClientContext context;

        Status status = stub_->Register(&context, request, &response);

        if (status.ok()) {
            std::cout << "Registration successful: " << response.session_id() << std::endl;
            return response.success();
        } else {
            std::cout << "Registration failed: " << status.error_message() << std::endl;
            return false;
        }
    }

    bool Initialize() {
        InitializeRequest request;
        InitializeResult response;
        ClientContext context;

        Status status = stub_->Initialize(&context, request, &response);

        if (status.ok()) {
            std::cout << "Initialization successful: " << response.protocol_version() << std::endl;
            return true;
        } else {
            std::cout << "Initialization failed: " << status.error_message() << std::endl;
            return false;
        }
    }

    bool HandleRequest(const std::string& method) {
        JSONRPCRequest request;
        request.set_jsonrpc("2.0");
        request.set_id("1");
        request.set_method(method);

        JSONRPCResponse response;
        ClientContext context;

        Status status = stub_->HandleRequest(&context, request, &response);

        if (status.ok()) {
            std::cout << "Request handled successfully" << std::endl;
            return true;
        } else {
            std::cout << "Request handling failed: " << status.error_message() << std::endl;
            return false;
        }
    }

    bool RegisterTool(const std::string& name, const std::string& description) {
        RegisterToolRequest request;
        auto* tool = request.mutable_tool();
        tool->set_name(name);
        tool->set_description(description);

        RegisterToolResponse response;
        ClientContext context;

        Status status = stub_->RegisterTool(&context, request, &response);

        if (status.ok()) {
            std::cout << "Tool registration successful: " << response.tool_id() << std::endl;
            return response.success();
        } else {
            std::cout << "Tool registration failed: " << status.error_message() << std::endl;
            return false;
        }
    }

    bool ListTools() {
        ListToolsRequest request;
        ListToolsResponse response;
        ClientContext context;

        Status status = stub_->ListTools(&context, request, &response);

        if (status.ok()) {
            std::cout << "Found " << response.tools_size() << " tools:" << std::endl;
            for (const auto& tool : response.tools()) {
                std::cout << "- " << tool.name() << ": " << tool.description() << std::endl;
            }
            return true;
        } else {
            std::cout << "Listing tools failed: " << status.error_message() << std::endl;
            return false;
        }
    }

    bool RegisterPrompt(const std::string& name, const std::string& content) {
        RegisterPromptRequest request;
        auto* prompt = request.mutable_prompt();
        prompt->set_name(name);
        prompt->set_content(content);

        RegisterPromptResponse response;
        ClientContext context;

        Status status = stub_->RegisterPrompt(&context, request, &response);

        if (status.ok()) {
            std::cout << "Prompt registration successful: " << response.prompt_id() << std::endl;
            return response.success();
        } else {
            std::cout << "Prompt registration failed: " << status.error_message() << std::endl;
            return false;
        }
    }

    bool GetPrompt(const std::string& name) {
        GetPromptRequest request;
        request.set_name(name);

        Prompt response;
        ClientContext context;

        Status status = stub_->GetPrompt(&context, request, &response);

        if (status.ok()) {
            std::cout << "Found prompt: " << response.name() << std::endl;
            std::cout << "Content: " << response.content() << std::endl;
            return true;
        } else {
            std::cout << "Getting prompt failed: " << status.error_message() << std::endl;
            return false;
        }
    }

    bool ListPrompts() {
        ListPromptsRequest request;
        ListPromptsResponse response;
        ClientContext context;

        Status status = stub_->ListPrompts(&context, request, &response);

        if (status.ok()) {
            std::cout << "Found " << response.prompts_size() << " prompts:" << std::endl;
            for (const auto& prompt : response.prompts()) {
                std::cout << "- " << prompt.name() << ": " << prompt.content() << std::endl;
            }
            return true;
        } else {
            std::cout << "Listing prompts failed: " << status.error_message() << std::endl;
            return false;
        }
    }

private:
    std::unique_ptr<MCPService::Stub> stub_;
};

int main(int argc, char** argv) {
    std::string target_address("localhost:50051");
    MCPClient client(
        grpc::CreateChannel(target_address, grpc::InsecureChannelCredentials())
    );

    // Test registration
    if (!client.Register("test_client")) {
        return 1;
    }

    // Test initialization
    if (!client.Initialize()) {
        return 1;
    }

    // Test request handling
    if (!client.HandleRequest("test_method")) {
        return 1;
    }

    // Test tool registration and listing
    if (!client.RegisterTool("test_tool", "A test tool")) {
        return 1;
    }
    if (!client.ListTools()) {
        return 1;
    }

    // Test prompt registration and listing
    if (!client.RegisterPrompt("test_prompt", "This is a test prompt")) {
        return 1;
    }
    if (!client.GetPrompt("test_prompt")) {
        return 1;
    }
    if (!client.ListPrompts()) {
        return 1;
    }

    return 0;
} 