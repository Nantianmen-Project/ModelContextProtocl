#include <iostream>
#include <memory>
#include <string>
#include <grpcpp/grpcpp.h>
#include "../pb/mcp_service.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

class MCPServiceImpl final : public mcp::MCPService::Service {
public:
    Status Register(ServerContext* context, const mcp::RegisterRequest* request,
                   mcp::RegisterResponse* response) override {
        std::cout << "Received registration request" << std::endl;
        
        // Set session ID
        response->set_session_id("test-session-id");
        response->set_success(true);
        
        // Set server capabilities
        auto* capabilities = response->mutable_capabilities();
        auto* tools = capabilities->mutable_tools();
        tools->set_list_changed(true);
        
        // Set server info
        auto* info = response->mutable_server_info();
        info->set_name("MCP Server");
        info->set_version("1.0.0");
        
        return Status::OK;
    }

    Status Initialize(ServerContext* context, const mcp::InitializeRequest* request,
                     mcp::InitializeResult* response) override {
        std::cout << "Received initialization request" << std::endl;
        
        // Set protocol version
        response->set_protocol_version("1.0.0");
        
        return Status::OK;
    }

    Status HandleRequest(ServerContext* context, const mcp::JSONRPCRequest* request,
                        mcp::JSONRPCResponse* response) override {
        std::cout << "Received JSON-RPC request: " << request->method() << std::endl;
        
        // Set JSON-RPC version
        response->set_jsonrpc("2.0");
        response->set_id(request->id());
        
        auto* result = response->mutable_result();
        auto* meta = result->mutable__meta();
        meta->mutable_additional_meta()->insert({"message", "Request received"});
        
        return Status::OK;
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