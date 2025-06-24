cmake_minimum_required(VERSION 3.10)
project(MCPDemo CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the path to your Protobuf installation
set(PROTOBUF_ROOT "/usr/local/protobuf-3.21.12")

# Define Protobuf imported targets manually
add_library(protobuf::libprotobuf STATIC IMPORTED)
set_target_properties(protobuf::libprotobuf PROPERTIES
    IMPORTED_LOCATION "${PROTOBUF_ROOT}/lib/libprotobuf.a"
    INTERFACE_INCLUDE_DIRECTORIES "${PROTOBUF_ROOT}/include"
)

# Set CMAKE_PREFIX_PATH to help find gRPC and other libraries in /usr/local
set(CMAKE_PREFIX_PATH "/usr/local" ${CMAKE_PREFIX_PATH})

# Find gRPC
find_package(gRPC CONFIG REQUIRED)

# Set include directories for project sources and generated protobuf files
include_directories(./src)
include_directories(../pb)

# Debugging: Print all include directories
get_directory_property(CURRENT_INCLUDE_DIRECTORIES INCLUDE_DIRECTORIES)
message(STATUS "Current Include Directories: ${CURRENT_INCLUDE_DIRECTORIES}")

# Define source files for protobuf and gRPC generated code
set(PROTO_SRCS
    ../pb/mcp.pb.cc
    ../pb/mcp_service.pb.cc
    ../pb/mcp_service.grpc.pb.cc
)

# Define source files for server and client
set(SERVER_SRCS src/server.cpp ${PROTO_SRCS})
set(CLIENT_SRCS src/client.cpp ${PROTO_SRCS})

# Add server executable
add_executable(server ${SERVER_SRCS})
target_link_libraries(server
    gRPC::grpc++
    gRPC::grpc
    gRPC::gpr
    protobuf::libprotobuf # Link to the manually defined Protobuf target
    # Add other necessary libraries if any, e.g., -lpthread -ldl
)

# Add client executable
add_executable(client ${CLIENT_SRCS})
target_link_libraries(client
    gRPC::grpc++
    gRPC::grpc
    gRPC::gpr
    protobuf::libprotobuf # Link to the manually defined Protobuf target
    # Add other necessary libraries if any, e.g., -lpthread -ldl
) 