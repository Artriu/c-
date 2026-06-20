#include <iostream>
#include <cstdlib>
#include <ctime>

int main()
{
    int No1 = 0;
    int No2 = 0;
    int No3 = 0;
    int No4 = 0;
    int No5 = 0;
    int No6 = 0;

    int I = 0;

    srand(time(NULL));

    for(I; I <= 100000; I++)
    {
        
        int num = (rand() % 6) + 1;

        std::cout << num;

        switch(num)
        {
        case 1:
            No1 += 1;
            break;
        case 2:
            No2 += 1;
            break;
        case 3:
            No3 += 1;
            break;
        case 4:
            No4 += 1;
            break;
        case 5:
            No5 += 1;
            break;
        case 6:
            No6 += 1;
            break;
        
        default:
            break;
        }

    }

    std::cout << "1:" << No1 << '\n';
    std::cout << "2:" << No2 << '\n';
    std::cout << "3:" << No3 << '\n';
    std::cout << "4:" << No4 << '\n';
    std::cout << "5:" << No5 << '\n';
    std::cout << "6:" << No6 << '\n';

    return 0;
}