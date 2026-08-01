#include "Menu.hpp"

inline void PrintPaddedMenuTasks(auto* IndividualContainer , int ExtraPaddingOrFixedPadding, bool IsFixedPadding){
    if (taskDetails == nullptr){
        std::cout << "Error: taskDetails is a nullptr. From Menu.cpp \n";
        return;
    }

    std::string ExtraSpace;

    // Finding the longest Title
    std::string longest = words[0]; 

    for (const std::string& str : ) {
        if (str.size() > longest.size()) {
            longest = str;
        }
    }

    // Padding
    if (IsFixedPadding) {
        ExtraSpace.append(ExtraPaddingOrFixedPadding, ' ');
    }
    else{
        int Padding = 
    }

    for (auto& task : *IndividualContainer){
        
        std::cout << task.Title << ExtraSpace << '\n';
    }
}
inline void PrintPaddedMenuContainers(auto* Containers, int ExtraPaddingOrFixedPadding, bool IsFixedPadding){
    if (Containers == nullptr){
        std::cout << "Error: Containers is a nullptr. From Menu.cpp \n";
        return;
    }

    for (auto& container : *Containers){
        std::cout << container.Title << '\n';
    }
}