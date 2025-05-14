#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>
#include "lexer.h"

class Parser {
public:
  Parser(Lexer &lexer);
  void parseFunctionDefinition();

private:
  Lexer &lexer;

  void expect(TokenType expected_type, const std::string &error_message);
  void expect(std::vector<TokenType> expected_types, const std::string &error_message);
  void parseReturnType();
  void parseParameterList();
  void parseExpression();
  void parseReturnStatement();
  void parseVariableDeclaration();
  void parseAssignmentStatement();
  void parseBlock();
  void parseStatement();
  void parseIfStatement();
  void parsePrimaryExpression();
  void parseMultiplicativeExpression();
  void parseAdditiveExpression();
  void parseRelationalExpression();
  void parseEqualityExpression();
  void parseWhileStatement();
  void parseDoWhileStatement();
};

#endif // PARSER_H 