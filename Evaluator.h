//
//  Evaluator.h
//  assignmen5
//
//  Created by Maria Goncharuk on 15.07.2026.
//

#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "AST.h"
#include <map>
#include <string>
#include <stdexcept>

class Enviroment {
private:
    std::map<std::string, double> variables;
public:
    void defineVariable(const std::string& name, double value) {
        if (variables.find(name) != variables.end()) {
            throw std::runtime_error("Immutability error: Variable '" + name + "' is already defined and cannot be reassigned.");
        }
        variables[name] = value;
    }
    double getVariable(const std::string& name) const {
        auto it = variables.find(name);
        if (it == variables.end()) {
            throw std::runtime_error("Unknown variable: " + name);
        }
        return it->second;
    }
};

class Evaluator {
private:
    Enviroment env;
    double evalNumber(NumberNode* node);
    double evalBinaryOp(BinaryOpNode* node);
    double evalVariable(VariableNode* node);
    double evalVarDecl(VarDecNode* node);
    double evalFunctionCall(FunctionCallNode* node);
public:
    double evaluate(ASTNode* node);
};

#endif // EVALUATOR_H
