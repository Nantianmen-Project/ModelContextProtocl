# 协议生成

protoc -I=./ --cpp_out=./pb_test --grpc_out=./pb_test --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` ./mcp.proto ./mcp_service.proto

