# MCP QuickType 客户端

这是一个基于 Model Context Protocol (MCP) 的 C++ 客户端实现，支持与各种 MCP 服务器进行交互，特别是高德地图服务器。

## 功能特性

- 支持加载 JSON 格式的 MCP 服务器配置
- 自动启动和管理 MCP 服务器进程
- 支持所有标准的 MCP 操作（初始化、工具调用、资源访问等）
- 跨平台支持（Windows、Linux、macOS）
- 异步操作支持
- 完整的错误处理和日志记录

## 依赖项

- C++17 或更高版本
- CMake 3.10 或更高版本
- Boost 库（system 组件）
- nlohmann/json 库

## 安装依赖

### Ubuntu/Debian
```bash
sudo apt-get update
sudo apt-get install build-essential cmake libboost-system-dev nlohmann-json3-dev
```

### macOS
```bash
brew install cmake boost nlohmann-json
```

### Windows
```bash
# 使用 vcpkg
vcpkg install boost-system nlohmann-json
```

## 编译

```bash
mkdir build
cd build
cmake ..
make
```

## 配置

客户端使用 JSON 格式的配置文件来定义 MCP 服务器。示例配置：

```json
{
    "mcpServers": {
        "amap-maps": {
            "command": "npx",
            "args": [
                "-y",
                "@amap/amap-maps-mcp-server"
            ],
            "env": {
                "AMAP_MAPS_API_KEY": "您在高德官网上申请的key"
            }
        }
    }
}
```

### 配置说明

- `mcpServers`: 包含所有 MCP 服务器配置的对象
- `command`: 启动服务器的命令
- `args`: 命令参数数组
- `env`: 环境变量映射

## 使用方法

### 基本使用

```cpp
#include "mcp_client.hpp"

int main() {
    // 创建客户端
    mcp::MCPClient client;
    
    // 加载配置
    std::string configJson = R"({
        "mcpServers": {
            "amap-maps": {
                "command": "npx",
                "args": ["-y", "@amap/amap-maps-mcp-server"],
                "env": {"AMAP_MAPS_API_KEY": "your-api-key"}
            }
        }
    })";
    
    if (!client.loadConfigFromJson(configJson)) {
        std::cerr << "配置加载失败: " << client.getLastError() << std::endl;
        return 1;
    }
    
    // 连接到服务器
    if (!client.connectToServer("amap-maps")) {
        std::cerr << "连接失败: " << client.getLastError() << std::endl;
        return 1;
    }
    
    // 初始化
    quicktype::InitializeRequest initRequest;
    // ... 设置初始化参数
    auto initFuture = client.initialize(initRequest);
    auto initResult = initFuture.get();
    
    // 列出工具
    quicktype::ListSRequest listRequest;
    auto toolsFuture = client.listTools(listRequest);
    auto toolsResult = toolsFuture.get();
    
    // 调用工具
    quicktype::CallToolRequest callRequest;
    // ... 设置工具调用参数
    auto callFuture = client.callTool(callRequest);
    auto callResult = callFuture.get();
    
    // 断开连接
    client.disconnect();
    
    return 0;
}
```

### 高级功能

#### 异步操作

所有操作都支持异步执行：

```cpp
auto future = client.listTools(request);
// 在后台执行其他操作
auto result = future.get(); // 等待结果
```

#### 错误处理

```cpp
try {
    auto result = client.callTool(request).get();
} catch (const std::exception& e) {
    std::cerr << "操作失败: " << e.what() << std::endl;
    std::cerr << "详细错误: " << client.getLastError() << std::endl;
}
```

#### 连接状态检查

```cpp
if (client.isConnected()) {
    // 执行操作
} else {
    std::cerr << "未连接到服务器" << std::endl;
}
```

## API 参考

### MCPClient 类

#### 构造函数
- `MCPClient()`: 创建新的客户端实例

#### 配置方法
- `bool loadConfig(const std::string& configPath)`: 从文件加载配置
- `bool loadConfigFromJson(const std::string& jsonConfig)`: 从 JSON 字符串加载配置

#### 连接管理
- `bool connectToServer(const std::string& serverName)`: 连接到指定的服务器
- `void disconnect()`: 断开连接
- `bool isConnected() const`: 检查连接状态

#### MCP 操作
- `std::future<InitializeResult> initialize(const InitializeRequest& request)`: 初始化连接
- `std::future<ListToolsResult> listTools(const ListSRequest& request)`: 列出可用工具
- `std::future<CallToolResult> callTool(const CallToolRequest& request)`: 调用工具
- `std::future<ListResourcesResult> listResources(const ListSRequest& request)`: 列出可用资源
- `std::future<ReadResourceResult> readResource(const ReadResourceRequest& request)`: 读取资源
- `std::future<void> setLogLevel(const SetLevelRequest& request)`: 设置日志级别

#### 工具方法
- `std::string getLastError() const`: 获取最后的错误信息

## 示例

运行示例程序：

```bash
./mcp_quicktype_client
```

示例程序会：
1. 加载高德地图服务器配置
2. 连接到服务器
3. 执行初始化
4. 列出可用工具和资源
5. 设置日志级别
6. 尝试调用地图工具
7. 断开连接

## 故障排除

### 常见问题

1. **编译错误**: 确保安装了所有必要的依赖项
2. **连接失败**: 检查服务器配置和网络连接
3. **权限错误**: 确保有足够的权限启动服务器进程
4. **API 密钥错误**: 确保提供了有效的高德地图 API 密钥

### 调试

启用详细日志：

```cpp
quicktype::SetLevelRequest setLevelRequest;
// 设置为 debug 级别
auto setLevelFuture = client.setLogLevel(setLevelRequest);
```

## 许可证

本项目采用 MIT 许可证。

## 贡献

欢迎提交 Issue 和 Pull Request！

## 相关链接

- [Model Context Protocol 规范](https://modelcontextprotocol.io/)
- [高德地图 API](https://lbs.amap.com/)
- [nlohmann/json](https://github.com/nlohmann/json)
- [Boost 库](https://www.boost.org/) 