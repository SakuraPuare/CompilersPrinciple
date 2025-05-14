#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include "token.h"

class Lexer {
private:
  std::istream &input_stream;
  char current_char;
  Token current_token;

  void readChar();
  void skipWhitespace();
  bool isDigit(char c);
  bool isAlpha(char c);
  bool isIdentifierChar(char c);
  Token readIdentifierOrKeyword();
  Token readNumber();
  Token getNextTokenInternal();

public:
  Lexer(std::istream &is);
  Token peekToken();
  void consumeToken();
};

#endif // LEXER_H 