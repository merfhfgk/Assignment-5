//
//  Parser.cpp
//  assignmen5
//
//  Created by Maria Goncharuk on 15.07.2026.
//

#include "Parser.h"

Parser::Parser(const std::vector<Token>& tokenList) : tokens(tokenList), pos(0) {}

Token Parser::currentToken() const {
    if (pos < tokens.size()){
        return tokens[pos];
    }
    return {TokenType::EndOfLine, ""};
}

void Parser::advance() {
    if (pos< tokens.size()) {
        pos++;
    }
}

void Parser::expect(TokenType type) {
    if (currentToken().type == type) {
        advance();
    } else {
        throw std::runtime_error("Unexpected token: " + currentToken().value);
    }
}

std::unique_ptr<ASTNode> Parser::parseExpression() {
    auto left = parseTerm();
    while(currentToken().type == TokenType::Plus || currentToken().type == TokenType::Minus) {
        char op = (currentToken().type == TokenType::Plus) ? '+' : '-';
        advance();
        auto right = parseTerm();
        left = std::make_unique<BinaryOpNode>(op, std::move(left), std::move(right));
    }
    return left;
}

std::unique_ptr<ASTNode> Parser::parseTerm() {
    auto left = parseFactor();
    while (currentToken().type == TokenType::Multiply || currentToken().type == TokenType::Divide) {
        char op = (currentToken().type == TokenType::Multiply) ? '*' : '/';
        advance();
        auto right = parseFactor();
        left = std::make_unique<BinaryOpNode>(op, std::move(left), std::move(right));
    }
    return left;
}

std::unique_ptr<ASTNode> Parser::parseFactor() {
    Token token = currentToken();
    if (token.type == TokenType::Minus){
        advance();
        auto right = parseFactor();
        return std::make_unique<BinaryOpNode>('-', std::make_unique<NumberNode>(0.0), std::move(right));
    }
    if (token.type == TokenType::Number){
        advance();
        return std::make_unique<NumberNode>(std::stod(token.value));
    }
    if (token.type == TokenType::LParen){
        advance();
        auto node = parseExpression();
        expect(TokenType::RParen);
        return node;
    }
    if (token.type == TokenType::Identifier){
        std::string name = token.value;
        advance();
        if (currentToken().type == TokenType::LParen){
            advance();
            std::vector<std::unique_ptr<ASTNode>> args;
            if (currentToken().type != TokenType::RParen){
                args.push_back(parseExpression());
                while (currentToken().type == TokenType::Comma) {
                    advance();
                    args.push_back(parseExpression());
                }
            }
            expect(TokenType::RParen);
            return std::make_unique<FunctionCallNode>(name, std::move(args));
        } else {
            return std::make_unique<VariableNode>(name);
        }
    }
    throw std::runtime_error("Unexpected token in factor: " + token.value);
}

std:: unique_ptr<ASTNode>Parser::parseStatement() {
    if(currentToken().type == TokenType::Def) {
        advance();
        if (currentToken().type != TokenType::Identifier) {
            throw std::runtime_error("Expected function name after 'def'");
        }
        std::string funcName = currentToken().value;
        advance();
        expect(TokenType::LParen);
        std::vector<std::string>params;
        if (currentToken().type != TokenType::RParen) {
            if (currentToken().type != TokenType::Identifier) throw std::runtime_error("Expected parameter name");
            params.push_back(currentToken().value);
            advance();
            while (currentToken().type == TokenType::Comma) {
                advance();
                if (currentToken().type != TokenType::Identifier) throw std::runtime_error("Expected parameter name after comma");
                params.push_back(currentToken().value);
                advance();
            }
        }
        expect(TokenType::RParen);
        expect(TokenType::LBrace);
        auto body = parseExpression();
        expect(TokenType::RBrace);
        return std::make_unique<FunctionDefNode>(funcName, std::move(params), std::move(body));
    }
    if (currentToken().type == TokenType::Var) {
        advance();
        if (currentToken().type != TokenType::Identifier) {
            throw std::runtime_error("Expected veriable name after 'var'");
        }
        std::string varName = currentToken().value;
        advance();
        expect(TokenType::Assign);
        auto expr = parseExpression();
        return std::make_unique<VarDecNode>(varName, std::move(expr));
    }
    return parseExpression();
}

std::unique_ptr<ASTNode> Parser::parse() {
    return parseStatement();
}
