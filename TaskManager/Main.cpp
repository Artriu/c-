#include <algorithm>
#include <iostream>
#include <optional>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cctype>

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

    std::string DeadLine = "30 / 12 / 9999";
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

std::vector<MultiTaskContainer> TaskContainers;

// Handed out by AddTask. Only ever goes up - a deleted task's number is never reused.
int NextTaskID = 1;

// Handed out by AddContainer, same rules as NextTaskID.
int NextContainerID = 1;

// Function Innitializations

void StringToIntForDate(std::string DDMMYYYY);
void UploadTasksToDrive();
void LoadTasksFromDrive();
void PrintContainers();
void SeedTestData();

int AddTask(IndividualTaskProperties* TaskDetailPtr, MultiTaskContainer* Container);
int RemoveTask(int TaskID, int ContainerID);

int AddContainer(MultiTaskContainer c);
int RemoveContainer(int ContainerID);

MultiTaskContainer* FindContainer(int ContainerID);

// Input
std::string ReadLine();
int ToInt(const std::string& Text);
char FirstLetter(const std::string& Text);

// Menus
void AddContainerFromInput();
void RemoveContainerFromInput();
void OpenContainerMenu(int ContainerID);
void AddTaskFromInput(int ContainerID);
void RemoveTaskFromInput(int ContainerID);
void PrintTasks(const MultiTaskContainer& Container);
std::string PriorityName(Priority p);
std::string LengthName(Length l);

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

        // Whole line in, then convert. Bad input becomes -1 and lands in default.
        int Selection = ToInt(ReadLine());

        switch (Selection)
        {
            case 1:
            {
                PrintContainers();

                // break inside the switch only leaves the switch, so the loop needs its own off switch
                bool InSubMenu = true;

                while (InSubMenu)
                {
                    std::cout << "Choose a option for the Containers" << '\n';
                    std::cout << "A. List"             << '\n';
                    std::cout << "B. Add Container"    << '\n';
                    std::cout << "C. Remove Container" << '\n';
                    std::cout << "D. Exit to Main"     << '\n';
                    std::cout << "Numbers 1 and above to select a container" << '\n';

                    std::string Line = ReadLine();

                    int ContainerNumber = ToInt(Line);
                    if (ContainerNumber >= 1){
                        OpenContainerMenu(ContainerNumber);
                        continue;
                    }

                    char Selection1 = FirstLetter(Line);

                    switch (Selection1)
                    {
                    case 'A':
                        PrintContainers();
                        break;

                    case 'B':
                        AddContainerFromInput();
                        break;

                    case 'C':
                        RemoveContainerFromInput();
                        break;

                    case 'D':
                        InSubMenu = false;
                        break;

                    default:
                        std::cout << "INVALID CHOICE" << '\n';
                        break;
                    }
                }
                continue;
            }

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

int AddTask(IndividualTaskProperties* TaskDetailsPtr, MultiTaskContainer* Container){
    if (TaskDetailsPtr == nullptr || Container == nullptr) return -1;

    TaskDetailsPtr->TaskID = NextTaskID;
    NextTaskID++;

    Container->Tasks.push_back(*TaskDetailsPtr);

    return TaskDetailsPtr->TaskID;
}

// 0 = removed, -1 = no such container or task
int RemoveTask(int TaskID, int ContainerID){
    MultiTaskContainer* Container = FindContainer(ContainerID);
    if (Container == nullptr) return -1;

    for (auto& t : Container->Tasks){
        if (t == std::nullopt || t->TaskID != TaskID) continue;

        t = std::nullopt;
        return 0;
    }
    return -1;
}

// Copies c in, gives it the next ID, returns that ID. Same idea as AddTask.
int AddContainer(MultiTaskContainer c){
    c.TaskContainerID = NextContainerID;
    NextContainerID++;

    TaskContainers.push_back(c);
    return c.TaskContainerID;
}

int RemoveContainer(int ContainerID){

    auto removed = std::erase_if(TaskContainers,
        [&] (auto& t) {
            return t.TaskContainerID == ContainerID;
        }
    );
    return removed > 0 ? 0 : -1;
}

MultiTaskContainer* FindContainer(int ContainerID){

    for (auto& c : TaskContainers){
        if (c.TaskContainerID == ContainerID) return &c;
    }
    return nullptr;
}

std::string ReadLine(){
    std::string Line;

    // Input closed (Ctrl+Z / terminal gone): nothing more will ever arrive, so quit instead of looping forever
    if (!std::getline(std::cin, Line)) std::exit(0);

    return Line;
}

int ToInt(const std::string& Text){
    try {
        std::size_t Used = 0;
        int Value = std::stoi(Text, &Used);

        // "12abc" -> stoi stops at 'a', so Used != size -> reject it
        if (Used != Text.size()) return -1;
        return Value;
    }
    catch (...) {
        // Not a number at all ("abc", "") or too big for an int
        return -1;
    }
}

// First letter, uppercased so 'a' and 'A' both work. Blank line gives ' '.
char FirstLetter(const std::string& Text){
    if (Text.empty()) return ' ';
    return std::toupper(static_cast<unsigned char>(Text[0]));
}

// ---- Container menu actions ----

void AddContainerFromInput(){
    MultiTaskContainer NewContainer;

    std::cout << "Container title: ";
    NewContainer.Title = ReadLine();
    if (NewContainer.Title.empty()){
        std::cout << "Cancelled - a container needs a title" << '\n';
        return;
    }

    std::cout << "Description (blank to skip): ";
    std::string Description = ReadLine();
    if (!Description.empty()) NewContainer.Description = Description;

    int ID = AddContainer(NewContainer);
    std::cout << "Added container " << ID << ". " << NewContainer.Title << '\n';
}

void RemoveContainerFromInput(){
    PrintContainers();
    std::cout << "ID of the container to remove: ";
    int ID = ToInt(ReadLine());

    MultiTaskContainer* Container = FindContainer(ID);
    if (Container == nullptr){
        std::cout << "No container with that ID" << '\n';
        return;
    }

    // Deleting a container deletes its tasks too, so double check
    std::cout << "Delete \"" << Container->Title << "\" and all its tasks? (y/n): ";
    if (FirstLetter(ReadLine()) != 'Y'){
        std::cout << "Kept it" << '\n';
        return;
    }

    RemoveContainer(ID);   // Container pointer is dead after this line - don't touch it
    std::cout << "Removed container " << ID << '\n';
}

// ---- Inside one container ----

void OpenContainerMenu(int ContainerID){
    MultiTaskContainer* Container = FindContainer(ContainerID);
    if (Container == nullptr){
        std::cout << "No container with ID " << ContainerID << '\n';
        return;
    }

    std::cout << '\n' << "== " << Container->Title << " ==" << '\n';
    std::cout << Container->Description << '\n';
    PrintTasks(*Container);

    // No flag needed here: this is its own function, so 'return' leaves the loop AND the menu
    while (true)
    {
        std::cout << "Choose a option for the Tasks" << '\n';
        std::cout << "A. List Tasks"   << '\n';
        std::cout << "B. Add Task"     << '\n';
        std::cout << "C. Remove Task"  << '\n';
        std::cout << "D. Back to Containers" << '\n';

        switch (FirstLetter(ReadLine()))
        {
        case 'A':
            // Look it up again instead of reusing the old pointer - the vector may have changed
            PrintTasks(*FindContainer(ContainerID));
            break;

        case 'B':
            AddTaskFromInput(ContainerID);
            break;

        case 'C':
            RemoveTaskFromInput(ContainerID);
            break;

        case 'D':
            return;

        default:
            std::cout << "INVALID CHOICE" << '\n';
            break;
        }
    }
}

void AddTaskFromInput(int ContainerID){
    IndividualTaskProperties NewTask;

    std::cout << "Task title: ";
    NewTask.Title = ReadLine();
    if (NewTask.Title.empty()){
        std::cout << "Cancelled - a task needs a title" << '\n';
        return;
    }

    std::cout << "Description (blank to skip): ";
    std::string Description = ReadLine();
    if (!Description.empty()) NewTask.Description = Description;

    std::cout << "Priority - 1. High  2. Medium  3. Low  (anything else = Low): ";
    switch (ToInt(ReadLine()))
    {
        case 1: NewTask.Priority = Priority::High;   break;
        case 2: NewTask.Priority = Priority::Medium; break;
        default: break;   // Low is already the default
    }

    std::cout << "Length - 1. Long  2. Medium  3. Small  (anything else = Small): ";
    switch (ToInt(ReadLine()))
    {
        case 1: NewTask.Length = Length::LongTask;   break;
        case 2: NewTask.Length = Length::MediumTask; break;
        default: break;   // SmallTask is already the default
    }

    std::cout << "Deadline DD / MM / YYYY (blank to skip): ";
    std::string DeadLine = ReadLine();
    if (!DeadLine.empty()) NewTask.DeadLine = DeadLine;

    int ID = AddTask(&NewTask, FindContainer(ContainerID));
    if (ID == -1) std::cout << "Couldn't add the task" << '\n';
    else          std::cout << "Added task " << ID << ". " << NewTask.Title << '\n';
}

void RemoveTaskFromInput(int ContainerID){
    MultiTaskContainer* Container = FindContainer(ContainerID);
    if (Container == nullptr) return;

    PrintTasks(*Container);
    std::cout << "ID of the task to remove: ";
    int TaskID = ToInt(ReadLine());

    if (RemoveTask(TaskID, ContainerID) == 0) std::cout << "Removed task " << TaskID << '\n';
    else                                      std::cout << "No task with that ID here" << '\n';
}

void PrintTasks(const MultiTaskContainer& Container){
    bool AnyTasks = false;

    for (const auto& t : Container.Tasks){
        if (t == std::nullopt) continue;   // removed task - skip the hole

        AnyTasks = true;
        std::cout << t->TaskID << ". " << t->Title
                  << "  [" << PriorityName(t->Priority) << " priority, "
                  << LengthName(t->Length) << ", due " << t->DeadLine << "]" << '\n';
        std::cout << "    " << t->Description << '\n';
    }

    if (!AnyTasks) std::cout << "No tasks yet." << '\n';
}

std::string PriorityName(Priority p){
    switch (p)
    {
        case Priority::High:   return "High";
        case Priority::Medium: return "Medium";
        case Priority::Low:    return "Low";
    }
    return "?";
}

std::string LengthName(Length l){
    switch (l)
    {
        case Length::LongTask:   return "Long";
        case Length::MediumTask: return "Medium";
        case Length::SmallTask:  return "Small";
    }
    return "?";
}

void PrintContainers(){

    std::cout << "Here are the containers : " << '\n';
    for (const auto& c : TaskContainers){
        std::cout << c.TaskContainerID << ". " << c.Title << '\n';
    }
}

void SeedTestData(){

    // 1. Make the container. It's a plain value now - no heap, no make_unique.
    MultiTaskContainer Work;

    // 2. Fill it in. Dot, because Work is the container itself.
    Work.Title           = "Work";
    Work.Description     = "Things for the job";

    // 3. The vector stores its own copy, and AddContainer hands out the ID.
    AddContainer(Work);

    MultiTaskContainer School;
    School.Title           = "School";
    School.Description     = "Assignments and revision";
    AddContainer(School);

    MultiTaskContainer Home;
    Home.Title           = "Home";
    Home.Description     = "Chores and errands";
    AddContainer(Home);
}