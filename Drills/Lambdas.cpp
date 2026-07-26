#include <iostream>

int main() {
    double pi = 22.0/7.0;
    std::string SacrificialLamb = "AHHHHHH";

    auto CircleArea =   [pi](double radius) {return (double)radius * (double)radius * pi;};
    auto IsAFactor =    [](int Quotient, int diviser) { if (Quotient % diviser == 0.0) { return 0; } return -1; };
    auto ChangeToZero = [&SacrificialLamb](){ SacrificialLamb = "Gone removed from existance"; };

    double radius = 7;
    double area = CircleArea(radius);

    std::cout << area << '\n';

    int Divisible = IsAFactor(25, 5);
    
    std::cout << Divisible << '\n';

    std::cout << SacrificialLamb << '\n';
    ChangeToZero();
    std::cout << SacrificialLamb << '\n';

    return 0;
}