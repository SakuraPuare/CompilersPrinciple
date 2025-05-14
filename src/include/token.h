#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum TokenType {
  TOKEN_OPERATOR_PLUS,          // +
  TOKEN_OPERATOR_MINUS,         // -
  TOKEN_OPERATOR_MULTIPLY,      // *
  TOKEN_OPERATOR_DIVIDE,        // /
  TOKEN_OPERATOR_GREATER,       // >
  TOKEN_OPERATOR_LESS,          // <
  TOKEN_OPERATOR_GREATER_EQUAL, // >=
  TOKEN_OPERATOR_LESS_EQUAL,    // <=
  TOKEN_OPERATOR_EQUAL_EQUAL,   // ==
  TOKEN_OPERATOR_NOT_EQUAL,     // !=
  TOKEN_OPERATOR_NOT,           // !
  TOKEN_OPERATOR_ASSIGN,        // =
  TOKEN_SEPARATOR_SEMICOLON,    // ;
  TOKEN_SEPARATOR_COMMA,        // ,
  TOKEN_LEFT_PAREN,             // (
  TOKEN_RIGHT_PAREN,            // )
  TOKEN_LEFT_BRACE,             // {
  TOKEN_RIGHT_BRACE,            // }
  TOKEN_LEFT_BRACKET,           // [
  TOKEN_RIGHT_BRACKET,          // ]
  TOKEN_SINGLE_QUOTE,           // '
  TOKEN_DOUBLE_QUOTE,           // "
  TOKEN_BACKSLASH,              // '\'
  // 关键字
  TOKEN_KEYWORD_INT,    // int
  TOKEN_KEYWORD_VOID,   // void
  TOKEN_KEYWORD_RETURN, // return
  TOKEN_KEYWORD_IF,     // if
  TOKEN_KEYWORD_ELSE,   // else
  TOKEN_KEYWORD_WHILE,  // while
  TOKEN_KEYWORD_FOR,    // for
  TOKEN_KEYWORD_BREAK,  // break
  TOKEN_KEYWORD_CONTINUE, // continue
  TOKEN_KEYWORD_DO,       // do

  // 其他类型
  TOKEN_IDENTIFIER, // identifier
  TOKEN_NUMBER,     // number

  TOKEN_EOF,  // 文件结束
  TOKEN_ERROR // 错误标记
};

struct Token {
  TokenType type;
  std::string value;

  std::string toString() const {
    return "TokenType: " + std::to_string(type) + ", Value: \"" + value + "\"";
  }
};

#endif // TOKEN_H 