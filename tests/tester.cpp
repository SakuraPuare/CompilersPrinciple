#include <gtest/gtest.h>
#include <filesystem>
#include <string>
#include <vector>
#include <future>
#include <thread>
#include <iostream>

// 获取测试文件列表
std::vector<std::string> getTestFiles() {
    std::vector<std::string> files;
    try {
        for (const auto& entry : std::filesystem::directory_iterator("tests/examples")) {
            if (entry.is_regular_file()) {
                std::string filename = entry.path().filename().string();
                // 只包含 test_开头的 cpp 文件，排除 tester.cpp
                if (filename != "tester.cpp" && filename.find("test_") == 0 && 
                    filename.substr(filename.size() - 4) == ".cpp") {
                    files.push_back(entry.path().string());
                }
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "获取测试文件时出错：" << e.what() << std::endl;
    }
    
    return files;
}

// 编译测试文件并运行
bool compileAndRunTest(const std::string& testFile) {
    std::string baseName = std::filesystem::path(testFile).stem().string();
    std::string outputExe = "tests/" + baseName + ".out";
    
    // 编译命令
    std::string compileCmd = "g++ -std=c++17 " + testFile + " -o " + outputExe + " 2> tests/compile_error_" + baseName + ".txt";
    
    std::cout << "编译文件：" << testFile << std::endl;
    int compileResult = system(compileCmd.c_str());
    
    if (compileResult != 0) {
        std::cerr << "编译失败：" << testFile << std::endl;
        return false;
    }
    
    // 运行测试程序
    std::string runCmd = outputExe + " > tests/output_" + baseName + ".txt 2> tests/run_error_" + baseName + ".txt";
    std::cout << "运行测试：" << testFile << std::endl;
    
    int runResult = system(runCmd.c_str());
    return runResult == 0;
}

// 多线程测试类
class MultiThreadedTest : public ::testing::Test {
protected:
    std::vector<std::string> testFiles;
    
    void SetUp() override {
        testFiles = getTestFiles();
    }
    
    void TearDown() override {
        // 清理临时文件
        for (const auto& file : testFiles) {
            std::string baseName = std::filesystem::path(file).stem().string();
            std::string outputExe = "tests/" + baseName + ".out";
            
            if (std::filesystem::exists(outputExe)) {
                std::filesystem::remove(outputExe);
            }
        }
    }
};

// 测试用例：单线程运行所有测试
TEST_F(MultiThreadedTest, RunTestsSequentially) {
    for (const auto& file : testFiles) {
        EXPECT_TRUE(compileAndRunTest(file)) << "测试失败：" << file;
    }
}

// 测试用例：多线程运行所有测试
TEST_F(MultiThreadedTest, RunTestsConcurrently) {
    std::vector<std::future<bool>> futures;
    
    // 获取可用的 CPU 线程数
    unsigned int numThreads = std::thread::hardware_concurrency();
    if (numThreads == 0) numThreads = 2;  // 默认至少用 2 个线程
    
    std::cout << "使用 " << numThreads << " 个线程进行测试" << std::endl;
    
    // 创建线程池
    for (const auto& file : testFiles) {
        futures.push_back(std::async(std::launch::async, compileAndRunTest, file));
    }
    
    // 等待所有测试完成并检查结果
    for (size_t i = 0; i < futures.size(); ++i) {
        EXPECT_TRUE(futures[i].get()) << "测试失败：" << testFiles[i];
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
