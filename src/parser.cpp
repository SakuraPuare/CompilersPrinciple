#include <iostream>
#include "parser.h"

Parser::Parser(Lexer &lexer) : lexer(lexer) {}

void Parser::expect(TokenType expected_type, const std::string &error_message) {
  if (lexer.peekToken().type == expected_type) {
    lexer.consumeToken();
  } else {
    std::cerr << "解析错误：" << error_message << " 期望的是：" << expected_type
              << ", 实际得到：" << lexer.peekToken().toString() << std::endl;
    exit(1);
  }
}

void Parser::expect(std::vector<TokenType> expected_types, const std::string &error_message) {
  std::string expected_types_str = "";
  for (TokenType type : expected_types) {
    expected_types_str += std::to_string(type) + " ";
  }
  for (TokenType type : expected_types) {
    if (lexer.peekToken().type == type) {
      lexer.consumeToken();
      return;
    }
  }
  std::cerr << "解析错误：" << error_message << " 期望的是："
            << expected_types_str << ", 实际得到："
            << lexer.peekToken().toString() << std::endl;
  exit(1);
}

void Parser::parseReturnType() {
  if (lexer.peekToken().type == TOKEN_KEYWORD_INT) {
    lexer.consumeToken();
  } else if (lexer.peekToken().type == TOKEN_KEYWORD_VOID) {
    lexer.consumeToken();
  } else {
    std::cerr << "解析错误：期望函数返回类型 (int 或 void)，但得到 "
              << lexer.peekToken().toString() << std::endl;
    exit(1);
  }
}

void Parser::parseParameterList() {
  expect(TOKEN_RIGHT_PAREN, "期望参数列表的结束括号 ')'");
}

void Parser::parsePrimaryExpression() {
  TokenType current_type = lexer.peekToken().type;

  if (current_type == TOKEN_NUMBER) {
    lexer.consumeToken();
  } else if (current_type == TOKEN_IDENTIFIER) {
    lexer.consumeToken();
  } else if (current_type == TOKEN_LEFT_PAREN) {
    expect(TOKEN_LEFT_PAREN, "期望左括号 '('");
    parseAdditiveExpression();
    expect(TOKEN_RIGHT_PAREN, "期望右括号 ')'");
  } else {
    std::cerr << "解析错误：期望基本表达式 (数字、标识符 或 '(')，但得到 "
              << lexer.peekToken().toString() << std::endl;
    exit(1);
  }
}

void Parser::parseMultiplicativeExpression() {
  parsePrimaryExpression();

  while (lexer.peekToken().type == TOKEN_OPERATOR_MULTIPLY ||
         lexer.peekToken().type == TOKEN_OPERATOR_DIVIDE) {
    lexer.consumeToken();
    parsePrimaryExpression();
  }
}

void Parser::parseAdditiveExpression() {
  parseMultiplicativeExpression();

  while (lexer.peekToken().type == TOKEN_OPERATOR_PLUS ||
         lexer.peekToken().type == TOKEN_OPERATOR_MINUS) {
    lexer.consumeToken();
    parseMultiplicativeExpression();
  }
}

void Parser::parseRelationalExpression() {
  parseAdditiveExpression();

  while (lexer.peekToken().type == TOKEN_OPERATOR_LESS ||
         lexer.peekToken().type == TOKEN_OPERATOR_GREATER ||
         lexer.peekToken().type == TOKEN_OPERATOR_LESS_EQUAL ||
         lexer.peekToken().type == TOKEN_OPERATOR_GREATER_EQUAL) {
    lexer.consumeToken();
    parseAdditiveExpression();
  }
}

void Parser::parseEqualityExpression() {
  parseRelationalExpression();

  while (lexer.peekToken().type == TOKEN_OPERATOR_EQUAL_EQUAL ||
         lexer.peekToken().type == TOKEN_OPERATOR_NOT_EQUAL) {
    lexer.consumeToken();
    parseRelationalExpression();
  }
}

void Parser::parseExpression() {
  parseEqualityExpression();
}

void Parser::parseReturnStatement() {
  expect(TOKEN_KEYWORD_RETURN, "期望 return 关键字");
  parseExpression();
  expect(TOKEN_SEPARATOR_SEMICOLON, "期望 return 语句后的分号 ';'");
}

void Parser::parseVariableDeclaration() {
  parseReturnType(); // Consumes the type token

  if (lexer.peekToken().type == TOKEN_IDENTIFIER) {
    std::string variable_name = lexer.peekToken().value;
    expect(TOKEN_IDENTIFIER, "期望变量名 (标识符)");
  } else {
    expect(TOKEN_IDENTIFIER, "期望变量名 (标识符)");
  }

  expect(TOKEN_SEPARATOR_SEMICOLON, "期望变量声明后的分号 ';'");
}

void Parser::parseIfStatement() {
  expect(TOKEN_KEYWORD_IF, "期望 if 关键字");
  expect(TOKEN_LEFT_PAREN, "期望 if 条件前的左括号 '('");
  parseExpression();
  expect(TOKEN_RIGHT_PAREN, "期望 if 条件后的右括号 ')'");

  // 解析 then 部分
  if (lexer.peekToken().type == TOKEN_LEFT_BRACE) {
    parseBlock();
  } else {
    parseStatement();
  }

  // 检查 else 子句
  if (lexer.peekToken().type == TOKEN_KEYWORD_ELSE) {
    lexer.consumeToken();
    // 解析 else 部分
    if (lexer.peekToken().type == TOKEN_LEFT_BRACE) {
      parseBlock();
    } else {
      parseStatement();
    }
  }
}

void Parser::parseWhileStatement() {
  expect(TOKEN_KEYWORD_WHILE, "期望 while 关键字");
  expect(TOKEN_LEFT_PAREN, "期望 while 条件前的左括号 '('");
  parseExpression();
  expect(TOKEN_RIGHT_PAREN, "期望 while 条件后的右括号 ')'");

  // 解析循环体
  if (lexer.peekToken().type == TOKEN_LEFT_BRACE) {
    parseBlock();
  } else {
    parseStatement();
  }
}

void Parser::parseStatement() {
  TokenType current_type = lexer.peekToken().type;

  if (current_type == TOKEN_LEFT_BRACE) {
    parseBlock();
    return;
  }

  if (current_type == TOKEN_KEYWORD_RETURN) {
    parseReturnStatement();
  } else if (current_type == TOKEN_KEYWORD_INT ||
             current_type == TOKEN_KEYWORD_VOID) {
    parseVariableDeclaration();
  } else if (current_type == TOKEN_IDENTIFIER) {
    parseAssignmentStatement();
  } else if (current_type == TOKEN_KEYWORD_IF) {
    parseIfStatement();
  } else if (current_type == TOKEN_KEYWORD_WHILE) {
    parseWhileStatement();
  } else if (current_type == TOKEN_KEYWORD_DO) {
    parseDoWhileStatement();
  }
  // ... 其他语句类型 (for, break, continue, etc.) ...
  else {
    std::cerr << "解析错误：无法识别的语句开始标记："
              << lexer.peekToken().toString() << std::endl;
    exit(1);
  }
}

void Parser::parseAssignmentStatement() {
  if (lexer.peekToken().type == TOKEN_IDENTIFIER) {
    std::string variable_name = lexer.peekToken().value;
    expect(TOKEN_IDENTIFIER, "期望赋值语句左侧的变量名 (标识符)");
  } else {
    expect(TOKEN_IDENTIFIER, "期望赋值语句左侧的变量名 (标识符)");
  }

  expect(TOKEN_OPERATOR_ASSIGN, "期望赋值运算符 '='");
  parseExpression();
  expect(TOKEN_SEPARATOR_SEMICOLON, "期望赋值语句后的分号 ';'");
}

void Parser::parseBlock() {
  expect(TOKEN_LEFT_BRACE, "期望函数体开始的左花括号 '{'");

  while (lexer.peekToken().type != TOKEN_RIGHT_BRACE &&
         lexer.peekToken().type != TOKEN_EOF) {
    parseStatement();
  }

  expect(TOKEN_RIGHT_BRACE, "期望函数体的结束花括号 '}'");
}

void Parser::parseFunctionDefinition() {
  parseReturnType();
  expect(TOKEN_IDENTIFIER, "期望函数名 (标识符)");
  expect(TOKEN_LEFT_PAREN, "期望函数名后的左括号 '('");
  parseParameterList();
  parseBlock();
}

void Parser::parseDoWhileStatement() {
  expect(TOKEN_KEYWORD_DO, "期望 do 关键字");
  parseStatement(); // 解析循环体
  expect(TOKEN_KEYWORD_WHILE, "期望 while 关键字");
  expect(TOKEN_LEFT_PAREN, "期望 do-while 条件前的左括号 '('");
  parseExpression(); // 解析条件表达式
  expect(TOKEN_RIGHT_PAREN, "期望 do-while 条件后的右括号 ')'");
  expect(TOKEN_SEPARATOR_SEMICOLON, "期望 do-while 语句后的分号 ';'");
} 