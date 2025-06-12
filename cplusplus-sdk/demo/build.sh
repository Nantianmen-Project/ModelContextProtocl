#!/bin/bash

# Create build directory
mkdir -p build

# Set include paths
PROTOBUF_INCLUDE="/usr/local/include"
GRPC_INCLUDE="/usr/local/include"
ABSL_INCLUDE="/usr/local/include"

# Compile server
g++ -std=c++17 \
    -I${PROTOBUF_INCLUDE} \
    -I${GRPC_INCLUDE} \
    -I${ABSL_INCLUDE} \
    -I. \
    demo/src/server.cpp \
    mcp.pb.cc \
    mcp_service.pb.cc \
    mcp_service.grpc.pb.cc \
    -L/usr/local/lib \
    -lgrpc++ \
    -lgrpc \
    -lprotobuf \
    -pthread \
    -o build/server

# Compile client
g++ -std=c++17 \
    -I${PROTOBUF_INCLUDE} \
    -I${GRPC_INCLUDE} \
    -I${ABSL_INCLUDE} \
    -I. \
    demo/src/client.cpp \
    mcp.pb.cc \
    mcp_service.pb.cc \
    mcp_service.grpc.pb.cc \
    -L/usr/local/lib \
    -lgrpc++ \
    -lgrpc \
    -lprotobuf \
    -pthread \
    -o build/client 