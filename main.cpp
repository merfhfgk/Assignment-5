//
//  main.cpp
//  assignmen5
//
//  Created by Maria Goncharuk on 14.07.2026.
//

#include <iostream>
#include <string>
#include "Lexer.h"

int main() {
    std::string input;
    std::cout << "--- lexer test ---\n";
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

        Lexer lexer(input);
        std::vector<Token> tokens = lexer.tokenize();        
        for (const auto& token : tokens) {
            std::cout << "[Type: " << static_cast<int>(token.type)
                      << ", Value: '" << token.value << "']\n";
        }
    }

    return 0;
}
