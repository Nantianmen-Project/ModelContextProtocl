#include <iostream>
#include <grpc/grpc.h>

int main() {
        std::cout << "gRPC version: " << grpc_version_string() << std::endl;
            return 0;
}

