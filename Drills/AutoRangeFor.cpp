#include <iostream>
#include <vector>
#include <string>

int main() {
    std::vector<int> nums = {1, 2, 3, 4, 5};

    std::vector<std::string> words = {"alpha", "beta", "gamma"};

    for (auto& n : nums){
        std::cout << n << '\n';

        n = n * 2;
    }

    for (auto n : words){
        std::cout << n << '\n';
    }

    for (auto n : nums){
        std::cout << n << '\n';
    }

    return 0;
}
