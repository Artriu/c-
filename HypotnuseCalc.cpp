#include <iostream>
#include <cmath>

int main() {
    double P;
    double B;
    double H;

    std::cin >> P;
    std::cin >> B;

    H = sqrt(pow(P, 2) + pow(B, 2));

    std::cout <<  H;
    return 0;
}