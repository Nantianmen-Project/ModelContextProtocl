#!/bin/bash

# 测试构建脚本

set -e

echo "测试 MCP QuickType 客户端构建"
echo "=============================="

# 检查当前目录
if [ ! -f "CMakeLists.txt" ]; then
    echo "错误: 请在项目根目录运行此脚本"
    exit 1
fi

# 清理之前的构建
echo "清理之前的构建..."
rm -rf build

# 运行构建脚本
echo "运行构建脚本..."
./build.sh

# 检查生成的文件
echo "检查生成的文件..."
if [ ! -f "build/mcp_quicktype_client" ]; then
    echo "错误: 主程序未生成"
    exit 1
fi

if [ ! -f "build/amap_example" ]; then
    echo "错误: 高德地图示例程序未生成"
    exit 1
fi

echo "✓ 构建测试成功!"
echo ""
echo "生成的文件:"
echo "  - build/mcp_quicktype_client"
echo "  - build/amap_example"
echo ""
echo "下一步:"
echo "  1. 获取高德地图 API 密钥"
echo "  2. 运行: ./build/amap_example <your_api_key>"
echo "  3. 或者编辑 config.json 文件并运行: ./build/amap_example --config config.json" 