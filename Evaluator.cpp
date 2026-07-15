//
//  Evaluator.cpp
//  assignmen5
//
//  Created by Maria Goncharuk on 15.07.2026.
//

#include "Evaluator.h"
#include <cmath> 
#include <algorithm>

double Evaluator::evaluate(ASTNode *node) {
    if (!node) return 0.0;
    if (auto n = dynamic_cast<NumberNode*>(node)) return evalNumber(n);
    if (auto n = dynamic_cast<BinaryOpNode*>(node)) return evalBinaryOp(n);
    if (auto n = dynamic_cast<VariableNode*>(node)) return evalVariable(n);
    if (auto n = dynamic_cast<VarDecNode*>(node)) return evalVarDecl(n);
    if (auto n = dynamic_cast<FunctionCallNode*>(node)) return evalFunctionCall(n);
    if (auto n = dynamic_cast<FunctionDefNode*>(node)) return evalFunctionDef(n);
    throw std::runtime_error("Unknown AST Node type");
}

double Evaluator::evalNumber(NumberNode* node) {
    return node->value;
}

double Evaluator::evalVariable(VariableNode *node) {
    return env.getVariable(node->name);
}

double Evaluator::evalVarDecl(VarDecNode *node) {
    double value = evaluate(node->expression.get());
    env.defineVariable(node->varName, value);
    return value;
}

double Evaluator::evalBinaryOp(BinaryOpNode *node) {
    double left = evaluate(node->left.get());
    double right = evaluate(node->right.get());
    switch (node->op) {
        case '+': return left + right;
        case '-': return left - right;
        case '*': return left * right;
        case '/': if (right == 0.0) throw std::runtime_error("Cant divide by 0");
            return left/right;
        default: throw std::runtime_error("Unknown operator");
    }
}

double Evaluator::evalFunctionCall(FunctionCallNode *node) {
    if (node->functionName == "max") {
        if (node->args.size() != 2) throw std::runtime_error("max requires 2 arguments");
        return std::max(evaluate(node->args[0].get()), evaluate(node->args[1].get()));
    }
    if (node->functionName == "min") {
        if (node->args.size() != 2) throw std::runtime_error("min requires 2 arguments");
        return std::min(evaluate(node->args[0].get()), evaluate(node->args[1].get()));
    }
    if (node->functionName == "pow") {
        if (node->args.size() != 2) throw std::runtime_error("pow requires 2 arguments");
        return std::pow(evaluate(node->args[0].get()), evaluate(node->args[1].get()));
    }
    if (node->functionName == "abs") {
        if (node->args.size() != 1) throw std::runtime_error("abs requires 1 arguments");
        return std::abs(evaluate(node->args[0].get()));
    }
    auto func = env.getFunction(node->functionName);
    if (node->args.size() != func.params.size()){
        throw std::runtime_error("Incorrect number of arguments for function '" + node->functionName + "'");
    }
    std::vector<double> argValues;
    for (size_t i = 0; i < node->args.size(); i++) {
        argValues.push_back(evaluate(node->args[i].get()));
    }
    Enviroment oldEnv = env;
    for(size_t i = 0; i < func.params.size(); i++){
        env.defineLocalVariable(func.params[i], argValues[i]);
    }
    double result = evaluate(func.body);
    env = oldEnv;
    return result;
}

double Evaluator::evalFunctionDef(FunctionDefNode* node) {
    env.defineFunction(node->name, node->params, node->body.get());
    return 0.0;
}
