#include <iostream>
#include <optional>
#include <fstream>
#include <vector>
#include <string>

// Enum Classes
enum class Priority : int {High    , Medium    , Low      };
enum class Length   : int {LongTask, MediumTask, SmallTask};

// DataStorage

// Individual Tasks
struct IndividualTaskProperties
{
    // Important
    int TaskID;
    std::string Title       = "Add Name";
    std::string Description = "Add Description";

    // Extras
    Priority    Priority = Priority::Low;
    Length      Length   = Length::SmallTask;

    std::string DeadLine = " 30 / 12 / 9999";
};

// Collection of Tasks
struct MultiTaskContainer
{
    // Important
    int TaskContainerID;
    std::string Title;
    std::string Description;

    std::vector<IndividualTaskProperties> Tasks;
};

std::vector<MultiTaskContainer> TaskContainers;

// Function Innitializations

void StringToIntForDate(std::string DDMMYYYY);
void UploadTasksToDrive();
void LoadTasksFromDrive();

int AddTask(IndividualTaskProperties* TaskDetailPtr, MultiTaskContainer* Container);
int RemoveTask(int TaskID);

// Main
int main () {
    IndividualTaskProperties Task1;
    Task1.Title = "Complete Add Task";
    Task1.Description = "None";

    MultiTaskContainer Today;
    Today.Title = "Today";
    Today.Description = "Hlo";
    Today.TaskContainerID = 123;

    AddTask(&Task1, &Today);

    for (auto& t : Today.Tasks){
        std::cout << t.Title       << '\n'
                  << t.Description << '\n'
                  << t.DeadLine    << '\n';
    }
        

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

int AddTask(IndividualTaskProperties* TaskDetailsPtr, MultiTaskContainer* Container){
    if (TaskDetailsPtr == nullptr || Container == nullptr) return -1;

    Container->Tasks.push_back(*TaskDetailsPtr);

    return 0;
}