#include <iostream>
#include <optional>
#include <vector>

std::optional<int> FindEven(std::vector<int> Numbers);

int main() {
    std::vector<int> Numbers = {1, 1, 1, 1, 1};

    auto Return = FindEven(Numbers);

    if (Return)
        std::cout << *Return;

    else {
        std::cout << "No even Number";
    }

    return 0;
}

std::optional<int> FindEven(std::vector<int> Numbers){
    for (int n : Numbers){
        if (n % 2 == 0){
            return n;
        }
    }

    return std::nullopt;
}