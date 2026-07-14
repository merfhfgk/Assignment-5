//
//  lexer.cpp
//  assignmen5
//
//  Created by Maria Goncharuk on 14.07.2026.
//

#include "Lexer.h"
#include <cctype>

Lexer::Lexer(const std::string& input) : text(input), pos(0) {}

Token Lexer::number(){
    std::string result;
    while(pos < text.length()&& (std::isdigit(text[pos]) || text[pos] == '.')){
        result += text[pos];
        pos++;
    }
    return {TokenType::Number, result};
}

Token Lexer::identifierOrKeyword(){
    std::string result;
    while(pos<text.length()&& std::isalnum(text[pos])) {
        result += text[pos];
        pos++;
    }
    if (result == "var") return {TokenType::Var, result};
    if (result == "def") return {TokenType::Def, result};
    return {TokenType::Identifier, result};
}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    while (pos < text.length()){
        char currentChar = text[pos];
        if (std::isspace(currentChar)){
            pos++;
            continue;
        }
        if (std::isdigit(currentChar)){
            tokens.push_back(number());
            continue;
        }
        if (std::isalpha(currentChar)){
            tokens.push_back(identifierOrKeyword());
            continue;
        }
        switch (currentChar) {
            case '+': tokens.push_back({TokenType::Plus, "+"}); break;
            case '-': tokens.push_back({TokenType::Minus, "-"}); break;
            case '*': tokens.push_back({TokenType::Multiply, "*"}); break;
            case '/': tokens.push_back({TokenType::Divide, "/"}); break;
            case '=': tokens.push_back({TokenType::Assign, "="}); break;
            case '(': tokens.push_back({TokenType::LParen, "("}); break;
            case ')': tokens.push_back({TokenType::RParen, ")"}); break;
            case '{': tokens.push_back({TokenType::LBrace, "{"}); break;
            case '}': tokens.push_back({TokenType::RBrace, "}"}); break;
            case ',': tokens.push_back({TokenType::Comma, ","}); break;
            default:  tokens.push_back({TokenType::Unknown, std::string(1, currentChar)});
            break;
        }
        pos++;
    }
    tokens.push_back({TokenType::EndOfLine, ""});
    return tokens;
}
