# 项目结构

```
mcp_quicktype_client/
├── schema.hpp                 # MCP协议schema定义（由quicktype生成）
├── json.hpp                   # nlohmann/json头文件包装
├── mcp_client.hpp             # MCP客户端头文件
├── mcp_client.cpp             # MCP客户端实现
├── main.cpp                   # 主程序示例
├── amap_example.cpp           # 高德地图专用示例程序
├── config.json                # 配置文件示例
├── CMakeLists.txt             # CMake构建配置
├── build.sh                   # 构建脚本
├── test_build.sh              # 测试构建脚本
├── README.md                  # 项目说明文档
└── PROJECT_STRUCTURE.md       # 本文件
```

## 文件说明

### 核心文件

- **schema.hpp**: 包含完整的MCP协议定义，由quicktype工具从JSON Schema生成
- **json.hpp**: nlohmann/json库的简单包装
- **mcp_client.hpp/cpp**: MCP客户端的核心实现，提供与MCP服务器交互的功能

### 示例程序

- **main.cpp**: 基本的MCP客户端使用示例
- **amap_example.cpp**: 专门用于高德地图服务器的交互示例

### 配置文件

- **config.json**: MCP服务器配置示例，包含高德地图服务器配置

### 构建文件

- **CMakeLists.txt**: CMake构建配置，支持跨平台编译
- **build.sh**: 自动化构建脚本，包含依赖检查和安装
- **test_build.sh**: 构建测试脚本，验证项目是否能正确编译

### 文档

- **README.md**: 完整的项目说明文档
- **PROJECT_STRUCTURE.md**: 项目结构说明（本文件）

## 编译输出

构建完成后，在 `build/` 目录下会生成：

- **mcp_quicktype_client**: 主程序可执行文件
- **amap_example**: 高德地图示例程序可执行文件
- **libmcp_client_lib.a**: 静态库文件

## 依赖关系

```
mcp_client_lib (库)
├── schema.hpp
├── json.hpp
├── nlohmann/json
└── Boost::system

mcp_quicktype_client (主程序)
└── mcp_client_lib

amap_example (高德地图示例)
└── mcp_client_lib
```

## 使用流程

1. **准备环境**: 安装必要的依赖（CMake、C++编译器、nlohmann/json、Boost）
2. **构建项目**: 运行 `./build.sh` 或 `./test_build.sh`
3. **配置服务器**: 编辑 `config.json` 或使用命令行参数提供API密钥
4. **运行示例**: 执行 `./build/amap_example <api_key>` 或 `./build/amap_example --config config.json` 