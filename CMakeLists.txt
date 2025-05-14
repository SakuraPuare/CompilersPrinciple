# 指定所需的最低 CMake 版本
cmake_minimum_required(VERSION 3.10)

# 项目名称
project(CompilersPrinciple)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加包含目录
include_directories(src/include)

# 启用测试
enable_testing()

# 添加源文件目录
add_subdirectory(src)

# 添加测试目录
add_subdirectory(tests)