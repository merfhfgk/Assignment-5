//
//  main.cpp
//  assignmen5
//
//  Created by Maria Goncharuk on 14.07.2026.
//

#include <iostream>
#include <string>
#include "Lexer.h"
#include "Parser.h"
#include "Evaluator.h"

int main() {
    std::string input;
    Evaluator evaluator;
    std::vector<std::unique_ptr<ASTNode>> astMemory;
    std::cout << "test\n";
    std::cout << "input:\n";
    
    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, input)) break;
        
        if (input == "exit" || input == "quit") {
            break;
        }
        if (input.empty()) {
            continue;
        }

        try {
            Lexer lexer(input);
            std::vector<Token> tokens = lexer.tokenize();

            Parser parser(tokens);
            std::unique_ptr<ASTNode> ast = parser.parse();

            if (ast) {
                double result = evaluator.evaluate(ast.get());
                astMemory.push_back(std::move(ast));
                std::cout << result << "\n";
            }
        }
        catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    }

    return 0;
}
