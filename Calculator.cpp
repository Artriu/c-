#include <iostream>

int main() {
    
    char op;
    int Num1;
    int Num2;
    int Out;

    std::cin >> Num1;
    std::cin >> op;
    std::cin >> Num2;

    switch(op){
        case '+':
            Out = Num1 + Num2;
            break;

        case '-':
            Out = Num1 - Num2;
            break;

        case '*':
            Out = Num1 * Num2;
            break;

        case '/':
            Out = Num1 / Num2;
            break;

        default:
            std::cout << "Invalid Operation";
    }
    std::cout << Out;
    return 0;
}