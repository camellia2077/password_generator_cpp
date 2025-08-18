#!/bin/bash

# 当任何命令失败时，立即退出脚本
set -e

# 获取脚本所在的绝对路径
# 这确保无论你从哪里运行此脚本，它都能找到正确的项目目录
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"

# 切换到脚本所在的目录
cd "$SCRIPT_DIR"

echo "==> Current directory: $(pwd)"

# 定义构建目录的名称
BUILD_DIR="build"

# 1. 创建构建目录（如果它不存在）
echo "==> Preparing build directory './${BUILD_DIR}'..."
mkdir -p "$BUILD_DIR"

# 2. 运行 CMake 来配置项目
#    -G "Ninja" 指定使用 Ninja 作为构建系统
#    -S .       指定源目录为当前目录 (SCRIPT_DIR)
#    -B ${BUILD_DIR} 指定构建目录
echo "==> Configuring project with CMake and Ninja..."
cmake -G "Ninja" -S . -B "$BUILD_DIR"

# 3. 使用 Ninja 进行编译
#    -C ${BUILD_DIR} 指示 ninja 在构建目录中执行
echo "==> Building project with Ninja..."
ninja -C "$BUILD_DIR"

echo ""
echo "==> Build complete!"
echo "==> Executables are in the '${BUILD_DIR}' directory."