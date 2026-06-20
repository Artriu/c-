#include <iostream>

double GetTotal(double Sales[], int Size);

int main()
{
    double Sales[] = {50.00, 29.99, 100.00, 9.99};
    int Size = sizeof(Sales)/sizeof(Sales[0]);
    double Total = GetTotal(Sales, Size);

    std::cout << Total;

    return 0;
}

double GetTotal(double Sales[], int Size){
    double Total = 0;

    for(int i = 1; i <= 5; i++){
        Total += Sales[i];
    }

    return Total;
}