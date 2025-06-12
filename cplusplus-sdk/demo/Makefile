# Compiler settings
CXX = g++
CXXFLAGS = -std=c++17 -pthread
INCLUDES = -I/usr/local/include -I. -I../pb

# Library paths and flags
LDFLAGS = -L/usr/local/lib
LIBS = -lgrpc++ -lgrpc -lprotobuf

# Source files
PROTO_SRCS = ../pb/mcp.pb.cc ../pb/mcp_service.pb.cc ../pb/mcp_service.grpc.pb.cc
SERVER_SRCS = src/server.cpp $(PROTO_SRCS)
CLIENT_SRCS = src/client.cpp $(PROTO_SRCS)

# Targets
SERVER_TARGET = build/server
CLIENT_TARGET = build/client

# Default target
all: $(SERVER_TARGET) $(CLIENT_TARGET)

# Create build directory
$(shell mkdir -p build)

# Server target
$(SERVER_TARGET): $(SERVER_SRCS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ $(LDFLAGS) $(LIBS) -o $@

# Client target
$(CLIENT_TARGET): $(CLIENT_SRCS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ $(LDFLAGS) $(LIBS) -o $@

# Clean target
clean:
	rm -f $(SERVER_TARGET) $(CLIENT_TARGET)

# Run targets
run-server: $(SERVER_TARGET)
	DYLD_LIBRARY_PATH=/usr/local/lib:$$DYLD_LIBRARY_PATH $<

run-client: $(CLIENT_TARGET)
	DYLD_LIBRARY_PATH=/usr/local/lib:$$DYLD_LIBRARY_PATH $<

.PHONY: all clean run-server run-client 