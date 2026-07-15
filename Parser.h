//
//  Perser.h
//  assignmen5
//
//  Created by Maria Goncharuk on 15.07.2026.
//

#ifndef PARSER_H
#define PARSER_H

#include "Lexer.h"
#include "AST.h"
#include <vector>
#include <memory>
#include <stdexcept>

class Parser {
private:
    std::vector<Token> tokens;
    size_t pos;
    Token currentToken() const;
    void advance();
    void expect(TokenType type);
    std::unique_ptr<ASTNode> parseStatement();
    std::unique_ptr<ASTNode> parseExpression();
    std::unique_ptr<ASTNode> parseTerm();
    std::unique_ptr<ASTNode> parseFactor();
public:
    Parser(const std::vector<Token>& tokenList);
    std::unique_ptr<ASTNode> parse();
};

#endif // PARSER_H
