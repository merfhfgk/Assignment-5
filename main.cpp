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
    std::cout << "--- Тест Лексера запущено ---\n";
    std::cout << "Введи вираз (або 'exit' для виходу):\n";
    
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

        // Виводимо всі токени, щоб побачити, як лексер розбив рядок
        for (const auto& token : tokens) {
            // Виводимо тип як число (код enum) та саме значення
            std::cout << "[Type: " << static_cast<int>(token.type)
                      << ", Value: '" << token.value << "']\n";
        }
    }

    return 0;
}
