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
    struct CustomFunction {
        std::vector<std::string> params;
        ASTNode* body;
    };
    std::map<std::string, CustomFunction> functions;
public:
    void defineLocalVariable(const std::string& name, double value) {
        variables[name] = value;
    }
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
    void defineFunction(const std::string& name, const std::vector<std::string>& params, ASTNode* body) {
        if (functions.find(name) != functions.end()) {
            throw std::runtime_error("Function '" + name + "' is already defined.");
        }
        functions[name] = {params, body};
    }
    CustomFunction getFunction(const std::string& name) const {
        auto it = functions.find(name);
        if (it == functions.end()) {
            throw std::runtime_error("Unknown function: " + name);
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
    double evalFunctionDef(FunctionDefNode* node);
public:
    double evaluate(ASTNode* node);
};

#endif // EVALUATOR_H
