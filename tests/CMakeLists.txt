# 添加测试
enable_testing()
# 添加 Google Test 链接
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# 创建测试可执行文件
add_executable(tester tester.cpp)
target_link_libraries(tester ${GTEST_BOTH_LIBRARIES} pthread)

# 添加测试
add_test(NAME tester COMMAND tester)
