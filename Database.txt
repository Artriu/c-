#include <iostream>

struct Database
{
    std::string Name;
    int Marks;
};

int FindElement(Database array[], int size, std::string element);
char Grading(int Marks);
void BubbleSort(int array[], int size);

int main()
{
    Database students[] = 
    {
        {"A", 80},
        {"B", 75},
        {"C", 95},
        {"D", 60}
    };

    char Continue = 'N';
    int Return;

    do{
        std::string Name;
        std::cout << "Enter the Name to cheak \n";
        std::cin >> Name;
        int size = sizeof(students)/sizeof(students[0]);

        if(Name == "1234")
        {
            char AdminContinue;
            std::cout << "Would you like to display all information currently present in the database?[Y/N]";
            std::cin >> AdminContinue;

            if(AdminContinue == 'Y' || AdminContinue == 'y')
            {
                for(int inte = 0; inte < size; inte++){
                    std::cout << students[inte].Name << ' ' << students[inte].Marks << "\n";
                }
            }
            else{
                continue;
            }

            AdminContinue = 'N';

            std::cout << "Would you like to organise the data by the highest to lowest marks?[Y/N]";
            std::cin >> AdminContinue;
            if(AdminContinue == 'Y' || AdminContinue == 'y')
            {
                int Index[size];

                for(int i = 0; i < size; i++)
                {
                    Index[i] = students[i].Marks;
                }
                
                BubbleSort(Index, size);
                
                Database Sorted[4];
                
                for(int i = 0; i < size; i++)
                {
                    for(int j = 0; j < size; j++)
                    {
                        if(Index[i] == students[j].Marks)
                        {
                            Sorted[i] = students[j];
                            break;
                        }
                    }
                }
                
                for(int i = 0; i < size; i++)
                {
                    students[i] = Sorted[i];
                }
                
                std::cout << "\nSorted Database:\n";
                
                for(int i = 0; i < size; i++)
                {
                    std::cout
                        << students[i].Name
                        << ' '
                        << students[i].Marks
                        << '\n';
                }
                            continue;
                            }
        }

        Return = FindElement(students, size, Name);

        if(Return == -1)
        {
            std::cout << "No such Name was found in the database \n";
            continue;
        }

        else
        {
            std::cout << "Would you like to see the details?[Y/N]";
            std::cin >> Continue;

            if(Continue == 'Y' || Continue == 'y'){
                std::cout << "This is the data of the student \n";

                char Grade = Grading(students[Return].Marks);

                std::cout << Grade << '\n';
                std::cout << students[Return].Marks << '\n';

                char Exit;

                std::cout << "Press 'A' to continue and 'B' to stop";
                std::cin >> Exit;

                if(Exit == 'A'){
                    continue;
                }
                else{
                    break;
                }
            }

        }

    }while(true);

    return 0;
}

int FindElement(Database array[], int size, std::string element)
{
    for(int i = 0; i < size; i++)
    {
        if(element == array[i].Name)
        {
           return i;
        }
    }
    return -1;
}

char Grading(int Marks)
{
    if(Marks >= 90){
        return 'A';
    }
    else if(Marks >= 80){
        return 'B';
    }
    else if(Marks >= 70){
        return 'C';
    }
    else if(Marks >= 60){
        return 'D';
    }
    else{
        return 'F';
    }
}
void BubbleSort(int array[], int size)
{
    int Temp;

    for(int i = 0; i < size - 1; i++)
    {
        for(int j = 0; j < size - i - 1; j++)
        {
            if(array[j] < array[j + 1])
            {
                Temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = Temp;
            }
        }
    }
}