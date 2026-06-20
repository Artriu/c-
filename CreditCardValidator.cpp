#include <iostream>

int GetDigits(const int Number);
int SumEvenDigits(const std::string CardNumber);
int SumOddDigits(const std::string CardNumber);

int main(){
    std::string CardNumber;

    std::cout << "Enter a card number# \n";
    std::cin >> CardNumber;

    int Result = SumEvenDigits(CardNumber) + SumOddDigits(CardNumber);

    if(Result % 10 == 0){
        std::cout << "Valid Credit Card Number";
    }
    else{
        std::cout << "Invalid Number";
    }

    return 0;
}

int GetDigits(const int Number){

    return Number % 10 + (Number / 10 % 10);
}

int SumEvenDigits(const std::string CardNumber){
    
    int sum = 0;

    for(int i = CardNumber.size() - 2; i >= 0; i -= 2){
        sum += GetDigits((CardNumber[i] - 48) * 2);
    }

    return sum;
}

int SumOddDigits(const std::string CardNumber){
    int sum = 0;

    for(int i = CardNumber.size() - 1; i >= 0; i -= 2){
        sum += GetDigits(CardNumber[i] - 48);
    }

    return sum;
}