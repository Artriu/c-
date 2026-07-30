#include <iostream>
#include <optional>
#include <fstream>
#include <vector>
#include <string>

// Function Innitializations

void StringToIntForDate(std::string DDMMYYYY);
void UploadTasksToDrive();
void LoadTasksFromDrive();

// DataStorage

struct TaskProperties
{
    // Enum Classes
    enum class Priority : int {High    , Medium    , Low      };
    enum class Type     : int {LongTask, MediumTask, SmallTask};

    Priority Priority;
    Type     Type    ;

    // Important
    std::string Title;
    std::string Description;

    // Characteristics
    int DeadLine;
    std::string DeadLineText;
};


int main () {
    std::string DDMMYYYY = "12 / 08 / 2026";
    StringToIntForDate(DDMMYYYY);
    return 0;
}

void StringToIntForDate(std::string DDMMYYYY){
    int PositionInText = 0;
    int Array[3] = {0, 0, 0};

    for (auto c : DDMMYYYY){
        if (std::isdigit(c)) {
            switch (PositionInText)
            {
            case 0:
                Array[0] += (c - '0') * 10;
                break;

            case 1:
                Array[0] += (c - '0');
                break;

            case 2:
                Array[1] += (c - '0') * 10;
                break;

            case 3:
                Array[1] += (c - '0');
                break;

            case 4:
                Array[2] += (c - '0') * 1000;
                break;

            case 5:
                Array[2] += (c - '0') * 100;
                break;

            case 6:
                Array[2] += (c - '0') * 10;
                break;

            case 7:
                Array[2] += (c - '0');
                break;

            default:
                break;
            }

            PositionInText++;
        }
    }

    for ( int IntValue : Array){
        std::cout << IntValue << '\n';
    }
}