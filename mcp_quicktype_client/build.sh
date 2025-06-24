#!/bin/bash

# MCP QuickType 客户端构建脚本

set -e

echo "MCP QuickType 客户端构建脚本"
echo "=============================="

# 检查依赖
echo "检查依赖..."

# 检查CMake
if ! command -v cmake &> /dev/null; then
    echo "错误: 未找到 cmake，请先安装 CMake"
    exit 1
fi

# 检查编译器
if ! command -v g++ &> /dev/null && ! command -v clang++ &> /dev/null; then
    echo "错误: 未找到 C++ 编译器，请安装 g++ 或 clang++"
    exit 1
fi

# 检查nlohmann/json
if ! pkg-config --exists nlohmann_json; then
    echo "警告: 未找到 nlohmann/json，尝试使用系统包管理器安装..."
    if command -v apt-get &> /dev/null; then
        echo "尝试使用 apt-get 安装..."
        sudo apt-get update
        sudo apt-get install -y nlohmann-json3-dev
    elif command -v brew &> /dev/null; then
        echo "尝试使用 brew 安装..."
        brew install nlohmann-json
    else
        echo "请手动安装 nlohmann/json 库"
        echo "Ubuntu/Debian: sudo apt-get install nlohmann-json3-dev"
        echo "macOS: brew install nlohmann-json"
        exit 1
    fi
fi

# 检查Boost
if ! pkg-config --exists boost_system; then
    echo "警告: 未找到 Boost system，尝试使用系统包管理器安装..."
    if command -v apt-get &> /dev/null; then
        echo "尝试使用 apt-get 安装..."
        sudo apt-get update
        sudo apt-get install -y libboost-system-dev
    elif command -v brew &> /dev/null; then
        echo "尝试使用 brew 安装..."
        brew install boost
    else
        echo "请手动安装 Boost 库"
        echo "Ubuntu/Debian: sudo apt-get install libboost-system-dev"
        echo "macOS: brew install boost"
        exit 1
    fi
fi

echo "依赖检查完成"

# 创建构建目录
echo "创建构建目录..."
mkdir -p build
cd build

# 配置项目
echo "配置项目..."
cmake ..

# 编译项目
echo "编译项目..."
make -j$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)

echo ""
echo "构建完成!"
echo "可执行文件位置:"
echo "  - build/mcp_quicktype_client (主程序)"
echo "  - build/amap_example (高德地图示例)"
echo ""
echo "使用方法:"
echo "  ./amap_example <your_amap_api_key>"
echo "  ./amap_example --config ../config.json"
echo ""
echo "注意: 请将 <your_amap_api_key> 替换为您的高德地图 API 密钥" 