#include "lexer.h"

void Lexer::readChar() { 
  current_char = input_stream.get(); 
}

void Lexer::skipWhitespace() {
  while (current_char != EOF) {
    if (std::isspace(current_char)) {
      readChar();
    } else if (current_char == '/') {
      input_stream.peek(); // 窥视下一个字符而不消耗
      char next_char = input_stream.peek();

      if (next_char == '/') {
        // 单行注释 //
        readChar(); // 消耗第一个 '/'
        readChar(); // 消耗第二个 '/'
        while (current_char != EOF && current_char != '\n' &&
               current_char != '\r') {
          readChar();
        }
      } else if (next_char == '*') {
        // 多行注释 /* ... */
        readChar(); // 消耗 '/'
        readChar(); // 消耗 '*'
        bool comment_closed = false;
        while (current_char != EOF) {
          if (current_char == '*') {
            readChar(); // 消耗 '*'
            if (current_char == '/') {
              readChar(); // 消耗 '/' - 注释结束
              comment_closed = true;
              break; // 退出内层注释跳过循环
            }
          } else {
            readChar(); // 跳过其他字符
          }
        }
        if (!comment_closed) {
           std::cerr << "词法错误：未结束的多行注释！" << std::endl;
           exit(1); // 或者返回错误标记
        }
      } else {
         break; // 退出 while 循环，让 getNextTokenInternal 处理 '/'
      }
    } else {
      break; // 退出 while 循环，由 getNextTokenInternal 处理这个字符
    }
  }
}

bool Lexer::isDigit(char c) { 
  return c >= '0' && c <= '9'; 
}

bool Lexer::isAlpha(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

// 判断是否是合法的标识符字符 (字母、数字、下划线)
bool Lexer::isIdentifierChar(char c) { 
  return isAlpha(c) || isDigit(c) || c == '_'; 
}

Token Lexer::readIdentifierOrKeyword() {
  std::string value = "";
  while (current_char != EOF && isIdentifierChar(current_char)) {
    value += current_char;
    readChar();
  }

  // 检查是否是关键字
  if (value == "int") {
    return {TOKEN_KEYWORD_INT, value};
  } else if (value == "return") {
    return {TOKEN_KEYWORD_RETURN, value};
  } else if (value == "if") {
    return {TOKEN_KEYWORD_IF, value};
  } else if (value == "else") {
    return {TOKEN_KEYWORD_ELSE, value};
  } else if (value == "while") {
    return {TOKEN_KEYWORD_WHILE, value};
  } else if (value == "for") {
    return {TOKEN_KEYWORD_FOR, value};
  } else if (value == "break") {
    return {TOKEN_KEYWORD_BREAK, value};
  } else if (value == "continue") {
    return {TOKEN_KEYWORD_CONTINUE, value};
  } else if (value == "void") {
    return {TOKEN_KEYWORD_VOID, value};
  } else if (value == "do") {
    return {TOKEN_KEYWORD_DO, value};
  }

  // 如果不是关键字，就是标识符
  return {TOKEN_IDENTIFIER, value};
}

Token Lexer::readNumber() {
  std::string value = "";
  while (current_char != EOF && isDigit(current_char)) {
    value += current_char;
    readChar();
  }
  return {TOKEN_NUMBER, value};
}

Token Lexer::getNextTokenInternal() {
  skipWhitespace();

  if (input_stream.eof() || current_char == EOF) {
    return {TOKEN_EOF, ""};
  }

  if (isDigit(current_char)) {
    return readNumber();
  } else if (isAlpha(current_char) || current_char == '_') {
    return readIdentifierOrKeyword();
  }

  char initial_char = current_char;
  readChar();

  switch (initial_char) {
  case '+':
    return {TOKEN_OPERATOR_PLUS, "+"};
  case '-':
    return {TOKEN_OPERATOR_MINUS, "-"};
  case '*':
    return {TOKEN_OPERATOR_MULTIPLY, "*"};
  case '/':
    return {TOKEN_OPERATOR_DIVIDE, "/"};
  case '=':
    if (current_char == '=') {
      readChar();
      return {TOKEN_OPERATOR_EQUAL_EQUAL, "=="};
    }
    return {TOKEN_OPERATOR_ASSIGN, "="};
  case '>':
    if (current_char == '=') {
      readChar();
      return {TOKEN_OPERATOR_GREATER_EQUAL, ">="};
    }
    return {TOKEN_OPERATOR_GREATER, ">"};
  case '<':
    if (current_char == '=') {
      readChar();
      return {TOKEN_OPERATOR_LESS_EQUAL, "<="};
    }
    return {TOKEN_OPERATOR_LESS, "<"};
  case '!':
    if (current_char == '=') {
      readChar();
      return {TOKEN_OPERATOR_NOT_EQUAL, "!="};
    }
    return {TOKEN_OPERATOR_NOT, "!"};
  case ';':
    return {TOKEN_SEPARATOR_SEMICOLON, ";"};
  case ',':
    return {TOKEN_SEPARATOR_COMMA, ","};
  case '(':
    return {TOKEN_LEFT_PAREN, "("};
  case ')':
    return {TOKEN_RIGHT_PAREN, ")"};
  case '{':
    return {TOKEN_LEFT_BRACE, "{"};
  case '}':
    return {TOKEN_RIGHT_BRACE, "}"};
  case '[':
    return {TOKEN_LEFT_BRACKET, "["};
  case ']':
    return {TOKEN_RIGHT_BRACKET, "]"};
  case '\'':
    return {TOKEN_SINGLE_QUOTE, "'"};
  case '"':
    return {TOKEN_DOUBLE_QUOTE, "\""};
  case '\\':
    return {TOKEN_BACKSLASH, "\\"};

  default:
    std::string error_val(1, initial_char);
    return {TOKEN_ERROR, "Unrecognized character: " + error_val};
  }
}

Lexer::Lexer(std::istream &is) : input_stream(is) {
  readChar(); // 构造时读取第一个字符
  current_token = getNextTokenInternal();
}

Token Lexer::peekToken() { 
  return current_token; 
}

void Lexer::consumeToken() { 
  current_token = getNextTokenInternal(); 
} 