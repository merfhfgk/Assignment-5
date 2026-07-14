//
//  lexer.h
//  assignmen5
//
//  Created by Maria Goncharuk on 14.07.2026.
//

#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>

enum class TokenType {
    Number, Identifier, Plus, Minus, Multiply, Devide, Assign, LParen, RParen, LBrace, RBrace,
    Come, Var, Def, EndOfLine, Unknown
};

struct Token {
    TokenType type;
    std::string value;
};

class Lexer {
private:
    std::string text;
    size_t pos;
    Token number();
    Token identifierOrKeyword();
public:
    Lexer(const std::string& input);
    std::vector<Token> tokenize();
};

#endif // LEXER_H
