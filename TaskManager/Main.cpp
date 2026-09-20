#include <algorithm>
#include <iostream>
#include <optional>
#include <fstream>
#include <memory>
#include <vector>
#include <string>
#include <cstdlib>

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
void PrintContainers();
void SeedTestData();

int AddTask(IndividualTaskProperties* TaskDetailPtr, MultiTaskContainer* Container);
int RemoveTask(int TaskID, int ContainerID);

int AddContainer(std::unique_ptr<MultiTaskContainer> c);
MultiTaskContainer* FindContainer(int ContainerID);

// Main
int main () {

    SeedTestData();   // temporary: gives us something to print. Delete once "Add Container" works.

    while (true)
    {
        std::cout << "Choose an option with the respective number" << '\n';
        std::cout << "1. Container List" << '\n';
        std::cout << "2. Load Data"      << '\n';
        std::cout << "3. Upload Data"    << '\n';
        std::cout << "4. Exit"           << '\n';

        int Selection;

        std::cin >> Selection;

        switch (Selection)
        {
            case 1:
                PrintContainers();
                continue;

            case 2:
                std::cout << "Unavailable" << '\n';
                continue;

            case 3:
                std::cout << "Unavailable" << '\n';
                continue;

            case 4:
                std::cout << "Closing";
                return 0;

            default:
                std::cout << "INVALID CHOICE" << '\n';
                continue;
        }
    }
    

    return 0;
}

// Function delarations

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

void PrintContainers(){
    for (const auto& c : TaskContainers){
        if (c != nullptr) {
            std::cout << c->Title << '\n';
        }
    }
}

void SeedTestData(){

    // 1. Build the container on the heap. Work owns it right now.
    auto Work = std::make_unique<MultiTaskContainer>();

    // 2. Fill it in. Arrow, because Work is a pointer to the container.
    Work->TaskContainerID = 1;
    Work->Title           = "Work";
    Work->Description     = "Things for the job";

    // 3. Hand ownership to the vector. After this line Work is empty - do not use it again.
    AddContainer(std::move(Work));

    auto School = std::make_unique<MultiTaskContainer>();
    School->TaskContainerID = 2;
    School->Title           = "School";
    School->Description     = "Assignments and revision";
    AddContainer(std::move(School));

    auto Home = std::make_unique<MultiTaskContainer>();
    Home->TaskContainerID = 3;
    Home->Title           = "Home";
    Home->Description     = "Chores and errands";
    AddContainer(std::move(Home));
}