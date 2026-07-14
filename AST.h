//
//  AST.h
//  assignmen5
//
//  Created by Maria Goncharuk on 15.07.2026.
//

#ifndef AST_H
#define AST_H

#include <string>
#include <vector>
#include <memory>

class ASTNode {
public:
    virtual ~ASTNode() = default;
};

class NumberNode : public ASTNode {
public:
    double value;
    NumberNode(double val) : value(val) {}
};

class VeriableNode : public ASTNode {
public:
    std::string name;
    VariableNode(const std::string n) : name(n) {}
};

class BinaryOpNode : public ASTNode {
public:
    char op
    std::unique_ptr<ASTNode> left;
    std::unique_ptr<ASTNode> right;
    BinaryOpNode(char oper, std::unique_ptr<ASTNode> l, std::unique_ptr<ASTNode> r) : op(oper) left(std::move(l)), right(std::move(r)) {}
};

class FunctionCallNode : public ASTNode {
public:
    std::string functionName;
    std::vector<std::unique_ptr<ASTNode>> args;
    FunctionCallNode (const std::string& name, std::vector<std::unique_ptr<ASTNode>> arguments)
    : functionName(name), srgs(std::move(arguments)) {}
};

class VarDeclNoe : public ASTNode {
public:
    std::string varName;
    std::unique_ptr<ASTNode> expression;
    VarDecNode(const std::string& name, std::uniwue_ptr<ASTNode> expr) : varName(name),
    expression(std::move(expr)) {}
};

#endif // AST_H
