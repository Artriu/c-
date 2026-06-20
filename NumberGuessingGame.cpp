#include <iostream>

int main()
{
    srand(time(NULL));

    int Guess;
    int Tries = 0;
    bool won = false;

    std::cout << "Enter the number you would like to guess! 1-10 \n";
    std::cin >> Guess;

    do{
        int num = rand() % 10 + 1;


        if(num == Guess)
        {
            std::cout << "You Won! \n";
            Tries += 1;
            std::cout << "Tries : " << Tries << '\n';
            won = true;
        }
        else
        {
            std::cout << "Try Again \n";
            Tries += 1;
            std::cin >> Guess;
        }
    }while(won == false);

    bool Exit = false;
    std::cout << "Press any key to Exit";
    std::cin >> Exit;
    return 0;
}