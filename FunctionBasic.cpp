#include <iostream>

void AAC(std::string Name);

int main()
{
    std::string Name;
    std::cout << "What is your name? \n";
    std::getline(std::cin, Name);

    AAC(Name);

    return 0;
}

void AAC(std::string Name)
{
    std::cout << "Your name is as follows \n";
    std::cout << Name;
}