# Compiler settings
CXX = g++
CXXFLAGS = -std=c++17 -I. -I../pb -I/usr/local/include

# Library paths and flags
LDFLAGS = -L/usr/local/lib
LIBS = -lgrpc++ -lgrpc -lprotobuf -lgrpc++_reflection

# Proto files
PROTO_SRCS = ../pb/mcp.pb.cc ../pb/mcp_service.pb.cc ../pb/mcp_service.grpc.pb.cc

# Server source files
SERVER_SRCS = mcp_server/src/mcp_server.cpp

# Client source files
CLIENT_SRCS = mcp_client/src/mcp_client.cpp

# Host source files
HOST_SRCS = host/src/host.cpp

# Object files
SERVER_OBJS = $(SERVER_SRCS:.cpp=.o)
CLIENT_OBJS = $(CLIENT_SRCS:.cpp=.o)
HOST_OBJS = $(HOST_SRCS:.cpp=.o)
PROTO_OBJS = $(PROTO_SRCS:.cc=.o)

# Targets
all: mcp-server-bin mcp-client-bin host-bin

mcp-server-bin: $(SERVER_OBJS) $(PROTO_OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LIBS)

mcp-client-bin: $(CLIENT_OBJS) $(PROTO_OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LIBS)

host-bin: $(HOST_OBJS) $(PROTO_OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(SERVER_OBJS) $(CLIENT_OBJS) $(HOST_OBJS) $(PROTO_OBJS)
	rm -f mcp-server-bin mcp-client-bin host-bin

run-server: mcp-server-bin
	LD_LIBRARY_PATH=/usr/local/lib ./mcp-server-bin

run-client: mcp-client-bin
	LD_LIBRARY_PATH=/usr/local/lib ./mcp-client-bin

run-host: host-bin
	LD_LIBRARY_PATH=/usr/local/lib ./host-bin

.PHONY: all clean run-server run-client run-host 