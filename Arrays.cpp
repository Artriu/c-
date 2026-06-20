#include <iostream>

int main(){
    std::string Name[] = { "A", "B", "C", "D"};
    int Xvalue[] =       {  8 ,  6 , 12 , 13, 14, 18 };

    for(int i = 0; i <= sizeof(Xvalue)/sizeof(int) - 1; i++)
    {
        Xvalue[i] += 1;
        std::cout << Xvalue[i] << "\n";
    }

    return 0;
}
