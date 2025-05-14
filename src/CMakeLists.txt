include_directories(include)

file(GLOB_RECURSE header_files "include/*.h")

# 收集所有源文件
file(GLOB_RECURSE SOURCES *.cpp)

# 除掉 main.cpp
list(FILTER SOURCES EXCLUDE REGEX "main.cpp")

message("SOURCES: ${SOURCES}")

# 创建编译器库
add_library(compiler_lib ${SOURCES})

add_executable(compiler main.cpp)
target_link_libraries(compiler compiler_lib) 