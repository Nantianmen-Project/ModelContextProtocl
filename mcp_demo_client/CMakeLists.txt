cmake_minimum_required(VERSION 3.10)
project(mcp_quicktype_client)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find nlohmann-json
find_package(nlohmann_json 3.2.0 REQUIRED)

# Include directories
include_directories(${CMAKE_SOURCE_DIR})

# Create library
add_library(mcp_client_lib
    mcp_client.cpp
)

# Link nlohmann-json to the library
target_link_libraries(mcp_client_lib nlohmann_json::nlohmann_json)

# Create main executable
add_executable(mcp_client
    main.cpp
)

# Link the library to main executable
target_link_libraries(mcp_client mcp_client_lib)

# Create amap example executable
add_executable(amap_example
    amap_example.cpp
)

# Link the library to amap example executable
target_link_libraries(amap_example mcp_client_lib)

# Create local file example executable
add_executable(local_file_example
    local_file_example.cpp
)

# Link nlohmann-json to local file example (it doesn't use mcp_client_lib)
target_link_libraries(local_file_example nlohmann_json::nlohmann_json)

# Create filesystem example executable
add_executable(filesystem_example
    filesystem_example.cpp
)

# Link the library to filesystem example executable
target_link_libraries(filesystem_example mcp_client_lib)

# Set output directories
set_target_properties(mcp_client PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

set_target_properties(amap_example PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

set_target_properties(local_file_example PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

set_target_properties(filesystem_example PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# 平台特定的设置
if(WIN32)
    # Windows特定设置
    target_link_libraries(mcp_client_lib kernel32)
else()
    # Unix/Linux特定设置
    target_link_libraries(mcp_client_lib pthread)
endif()

# 编译选项
target_compile_options(mcp_client_lib PRIVATE
    $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra -Wpedantic>
    $<$<CXX_COMPILER_ID:Clang>:-Wall -Wextra -Wpedantic>
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
)

target_compile_options(local_file_example PRIVATE
    $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra -Wpedantic>
    $<$<CXX_COMPILER_ID:Clang>:-Wall -Wextra -Wpedantic>
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
)

# 安装规则
install(TARGETS mcp_client amap_example local_file_example filesystem_example
    RUNTIME DESTINATION bin
)

install(TARGETS mcp_client_lib
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

# 安装头文件
install(FILES ${HEADERS}
    DESTINATION include/${PROJECT_NAME}
) 