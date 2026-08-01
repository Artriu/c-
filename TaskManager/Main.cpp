#include <algorithm>
#include <iostream>
#include <optional>
#include <fstream>
#include <memory>
#include <vector>
#include <string>
#include <cstdlib>
#include "Menu.h"

//Memory
struct  Noisy
{
    Noisy()  { std::cout << "Born" << '\n'; };
    ~Noisy() { std::cout << "Died" << '\n'; };
};

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
    std::string Title       = "None";
    std::string Description = "None";

    std::vector<std::optional<IndividualTaskProperties>> Tasks;
};

std::vector<std::unique_ptr<MultiTaskContainer>> TaskContainers;

// Function Innitializations

void StringToIntForDate(std::string DDMMYYYY);
void UploadTasksToDrive();
void LoadTasksFromDrive();

int AddTask(IndividualTaskProperties* TaskDetailPtr, MultiTaskContainer* Container);
int RemoveTask(int TaskID, int ContainerID);

int AddContainer(std::unique_ptr<MultiTaskContainer> c);
MultiTaskContainer* FindContainer(int ContainerID);

// Main
int main () {
    int choice = 0;

    while (choice != 5){

        system("cls");

        std::cout << '\n';
        PrintPaddedList({"1. Add Container", "2. Add Task", "3. Remove Task", "4. Print Everything", "5. Quit"});
        std::cout << "Choice : ";

        std::cin >> choice;

        if (choice == 1){
            std::string title;
            int containerID;

            std::cout << "Container Title : ";
            std::cin  >> title;
            std::cout << "Container ID    : ";
            std::cin  >> containerID;

            auto NewContainer = std::make_unique<MultiTaskContainer>();
            NewContainer->Title           = title;
            NewContainer->TaskContainerID = containerID;

            AddContainer(std::move(NewContainer));
        }
        else if (choice == 2){
            int containerID;
            std::cout << "Add task to which Container ID : ";
            std::cin  >> containerID;

            MultiTaskContainer* Container = FindContainer(containerID);

            if (Container == nullptr){
                std::cout << "No container with that ID." << '\n';
            }
            else {
                IndividualTaskProperties NewTask;
                int priorityChoice, lengthChoice;

                std::cout << "Task ID       : ";
                std::cin  >> NewTask.TaskID;
                std::cout << "Title         : ";
                std::cin  >> NewTask.Title;
                std::cout << "Description   : ";
                std::cin  >> NewTask.Description;
                std::cout << "Priority (0=High, 1=Medium, 2=Low) : ";
                std::cin  >> priorityChoice;
                std::cout << "Length (0=Long, 1=Medium, 2=Small) : ";
                std::cin  >> lengthChoice;
                std::cout << "Deadline (e.g. 12/08/2026, no spaces) : ";
                std::cin  >> NewTask.DeadLine;

                NewTask.Priority = static_cast<Priority>(priorityChoice);
                NewTask.Length   = static_cast<Length>(lengthChoice);

                AddTask(&NewTask, Container);
            }
        }
        else if (choice == 3){
            int taskID, containerID;
            std::cout << "Task ID      : ";
            std::cin  >> taskID;
            std::cout << "Container ID : ";
            std::cin  >> containerID;

            RemoveTask(taskID, containerID);
        }
        else if (choice == 4){
            for (auto& c : TaskContainers){
                std::cout << "[Container] " << c->Title << " (ID " << c->TaskContainerID << ")\n";

                for (auto& t : c->Tasks){
                    if (!t) continue;
                    std::cout << "  - " << t->Title << " | " << t->Description
                              << " | due " << t->DeadLine << '\n';
                }
            }
        }

        if (choice != 5){
            std::cout << "\nPress Enter to continue...";
            std::cin.ignore();
            std::cin.get();
        }
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

int RemoveTask(int TaskID, int ContainerID){
    for (auto& c : TaskContainers){
        if (c->TaskContainerID != ContainerID) continue;

        for (auto& t : c->Tasks){
            if (t->TaskID != TaskID) continue;

            t = std::nullopt;
        };
    }
    return 0;
}

int AddContainer(std::unique_ptr<MultiTaskContainer> c){
    if (c == nullptr) return -1;

    TaskContainers.push_back(std::move(c));
    return 0;
}

MultiTaskContainer* FindContainer(int ContainerID){
    for (auto& c : TaskContainers){
        if (c->TaskContainerID == ContainerID) return c.get();
    }
    return nullptr;
}