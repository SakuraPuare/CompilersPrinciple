#include <iostream>
#include <fstream>
#include "lexer.h"
#include "parser.h"

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
    return 1;
  }

  std::ifstream file(argv[1]);
  if (!file.is_open()) {
    std::cerr << "Error opening file!" << std::endl;
    return 1;
  }

  Lexer lexer(file);
  Parser parser(lexer);

  try {
    // 调用解析函数定义的函数
    // 假设文件内容就是一个函数定义，并且以 EOF 结束
    parser.parseFunctionDefinition();

    // 解析完后，期望到达文件末尾
    if (lexer.peekToken().type == TOKEN_EOF) {
      std::cout << "解析成功，到达文件末尾。" << std::endl;
      return 0; // 解析成功
    } else {
      std::cerr << "解析错误：解析完成后还有其他标记！"
                << " 当前标记：" << lexer.peekToken().toString() << std::endl;
      return 1; // 解析失败
    }
  } catch (const std::exception &e) {
    std::cerr << "发生异常：" << e.what() << std::endl;
    return 1;
  }

  file.close();
  return 0;
}