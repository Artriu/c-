#include <iostream>

int main(){
    int age;
    std::cout << "What is your age?";
    std::cin >> age;
    std::cout << "You are " << age << " Years old!";
    std::cin >> age;

    return 0;
}