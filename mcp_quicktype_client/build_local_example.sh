#!/bin/bash

echo "=== Building Local File Example ==="

# 检查是否安装了必要的工具
if ! command -v g++ &> /dev/null; then
    echo "❌ Error: g++ compiler not found"
    exit 1
fi

if ! command -v cmake &> /dev/null; then
    echo "❌ Error: cmake not found"
    exit 1
fi

# 创建构建目录
mkdir -p build
cd build

# 运行CMake配置
echo "📋 Configuring with CMake..."
cmake .. -DCMAKE_BUILD_TYPE=Release

if [ $? -ne 0 ]; then
    echo "❌ CMake configuration failed"
    exit 1
fi

# 编译
echo "🔨 Compiling..."
if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    make -j$(nproc)
elif [[ "$OSTYPE" == "darwin"* ]]; then
    make -j$(sysctl -n hw.ncpu)
else
    make
fi

if [ $? -ne 0 ]; then
    echo "❌ Compilation failed"
    exit 1
fi

# 检查生成的可执行文件
if [ -f "bin/local_file_example" ]; then
    echo "✅ Local file example compiled successfully!"
    echo "   Executable: build/bin/local_file_example"
    echo ""
    echo "To run the example:"
    echo "   cd .. && ./build/bin/local_file_example"
else
    echo "❌ Executable not found after compilation"
    exit 1
fi

echo ""
echo "=== Build completed ===" 