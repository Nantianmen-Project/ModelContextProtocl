#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

#include <grpcpp/grpcpp.h>
#include "mcp_service.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
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

class MCPServiceImpl final : public MCPService::Service {
private:
    std::unordered_map<std::string, InputSchema> schemas_;
    std::unordered_map<std::string, Prompt> prompts_;
    std::unordered_map<std::string, mcp::Tool> tools_;

public:
    Status Register(ServerContext* context, const RegisterRequest* request, RegisterResponse* response) override {
        std::cout << "Received registration request from client: " << request->client_id() << std::endl;
        response->set_success(true);
        response->set_session_id("session_" + request->client_id());
        return Status::OK;
    }

    Status Initialize(ServerContext* context, const InitializeRequest* request, InitializeResult* response) override {
        std::cout << "Received initialization request" << std::endl;
        response->set_protocol_version("1.0.0");
        return Status::OK;
    }

    Status HandleRequest(ServerContext* context, const JSONRPCRequest* request, JSONRPCResponse* response) override {
        std::cout << "Received request: " << request->method() << std::endl;
        response->set_jsonrpc("2.0");
        response->set_id(request->id());
        return Status::OK;
    }

    Status HandleNotification(ServerContext* context, const JSONRPCNotification* request, Empty* response) override {
        std::cout << "Received notification: " << request->method() << std::endl;
        return Status::OK;
    }

    Status HandleBatchRequest(ServerContext* context, const JSONRPCBatchRequest* request, JSONRPCBatchResponse* response) override {
        std::cout << "Received batch request with " << request->requests_size() << " requests" << std::endl;
        return Status::OK;
    }

    Status RegisterInputSchema(ServerContext* context, const RegisterInputSchemaRequest* request, RegisterInputSchemaResponse* response) override {
        std::cout << "Registering input schema for tool: " << request->tool_name() << std::endl;
        schemas_[request->tool_name()] = request->schema();
        response->set_success(true);
        response->set_schema_id("schema_" + request->tool_name());
        return Status::OK;
    }

    Status GetInputSchema(ServerContext* context, const GetInputSchemaRequest* request, InputSchema* response) override {
        auto it = schemas_.find(request->tool_name());
        if (it != schemas_.end()) {
            *response = it->second;
            return Status::OK;
        }
        return Status(grpc::StatusCode::NOT_FOUND, "Schema not found");
    }

    Status ListResources(ServerContext* context, const ListResourcesRequest* request, ListResourcesResult* response) override {
        std::cout << "Listing resources" << std::endl;
        return Status::OK;
    }

    Status ReadResource(ServerContext* context, const ReadResourceRequest* request, ReadResourceResult* response) override {
        std::cout << "Reading resource: " << request->params().uri() << std::endl;
        return Status::OK;
    }

    Status RegisterTool(ServerContext* context, const RegisterToolRequest* request, RegisterToolResponse* response) override {
        std::cout << "Registering tool: " << request->tool().name() << std::endl;
        tools_[request->tool().name()] = request->tool();
        response->set_success(true);
        response->set_tool_id("tool_" + request->tool().name());
        return Status::OK;
    }

    Status ListTools(ServerContext* context, const ListToolsRequest* request, ListToolsResponse* response) override {
        std::cout << "Listing tools" << std::endl;
        for (const auto& tool : tools_) {
            *response->add_tools() = tool.second;
        }
        return Status::OK;
    }

    Status RegisterPrompt(ServerContext* context, const RegisterPromptRequest* request, RegisterPromptResponse* response) override {
        std::cout << "Registering prompt: " << request->prompt().name() << std::endl;
        prompts_[request->prompt().name()] = request->prompt();
        response->set_success(true);
        response->set_prompt_id("prompt_" + request->prompt().name());
        return Status::OK;
    }

    Status GetPrompt(ServerContext* context, const GetPromptRequest* request, Prompt* response) override {
        auto it = prompts_.find(request->name());
        if (it != prompts_.end()) {
            *response = it->second;
            return Status::OK;
        }
        return Status(grpc::StatusCode::NOT_FOUND, "Prompt not found");
    }

    Status ListPrompts(ServerContext* context, const ListPromptsRequest* request, ListPromptsResponse* response) override {
        std::cout << "Listing prompts" << std::endl;
        for (const auto& prompt : prompts_) {
            *response->add_prompts() = prompt.second;
        }
        return Status::OK;
    }

    Status UpdatePrompt(ServerContext* context, const UpdatePromptRequest* request, UpdatePromptResponse* response) override {
        std::cout << "Updating prompt: " << request->name() << std::endl;
        auto it = prompts_.find(request->name());
        if (it != prompts_.end()) {
            prompts_[request->name()] = request->prompt();
            response->set_success(true);
            return Status::OK;
        }
        return Status(grpc::StatusCode::NOT_FOUND, "Prompt not found");
    }

    Status DeletePrompt(ServerContext* context, const DeletePromptRequest* request, DeletePromptResponse* response) override {
        std::cout << "Deleting prompt: " << request->name() << std::endl;
        auto it = prompts_.find(request->name());
        if (it != prompts_.end()) {
            prompts_.erase(it);
            response->set_success(true);
            return Status::OK;
        }
        return Status(grpc::StatusCode::NOT_FOUND, "Prompt not found");
    }
};

void RunServer() {
    std::string server_address("0.0.0.0:50051");
    MCPServiceImpl service;

    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;
    server->Wait();
}

int main(int argc, char** argv) {
    RunServer();
    return 0;
} 