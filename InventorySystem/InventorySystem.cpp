#include <iostream>
#include <vector>
#include <fstream>

struct item{

    // Constants
    std::string name;
    int IDno;

    // Editable
    int count;
    int MaxItems;

    // Optional
    int Durability;
};

// Globals

std::vector<item> Inventory;
int InventorySize = 30;

// Function Declations

void AddItem(std::string TakenName, int TakenCount, int TakenMaxItems, int TakenIDno);
void RemoveItem(int IDno);
void PrintInventory();
void UploadinventoryToDrive();

int main(){

    // Give the vector its 30 empty slots (all fields zeroed)
    Inventory.resize(InventorySize);

    int choice = 0;

    while (choice != 4){

        // Menu
        std::cout << '\n'
                  << "1. Add Item"        << '\n'
                  << "2. Remove Item"     << '\n'
                  << "3. Print Inventory" << '\n'
                  << "4. Quit"            << '\n'
                  << "Choice : ";

        std::cin >> choice;

        if (choice == 1){
            std::string name;
            int count, maxItems, IDno;

            std::cout << "Name      : ";
            std::cin  >> name;
            std::cout << "Count     : ";
            std::cin  >> count;
            std::cout << "Max Count : ";
            std::cin  >> maxItems;
            std::cout << "ID Number : ";
            std::cin  >> IDno;

            AddItem(name, count, maxItems, IDno);
        }
        else if (choice == 2){
            int IDno;
            std::cout << "ID to remove : ";
            std::cin  >> IDno;

            RemoveItem(IDno);
        }
        else if (choice == 3){
            PrintInventory();
        }
    }

    return 0;
}

// Function Initialisation

void AddItem(std::string TakenName, int TakenCount, int TakenMaxItems, int TakenIDno){
    for (int i = 0; i < InventorySize; i++){

        // Empty slot = space to place the item
        if (Inventory[i].IDno == 0) {
            std::cout << "Space Available" << '\n';

            Inventory[i].name     = TakenName;
            Inventory[i].count    = TakenCount;
            Inventory[i].MaxItems = TakenMaxItems;
            Inventory[i].IDno     = TakenIDno;
            return;
        }
    }

    // No empty slot found
    std::cout << "No Space" << '\n';
}

void RemoveItem(int IDnum){
    for (unsigned int i = 0; i < Inventory.size() ; i++){
        if (Inventory[i].IDno == IDnum){
            std::cout << '\n'
                      << "The Item being Removed is : " << '\n'
                      << "Name      :" << Inventory[i].name << '\n'
                      << "Count     :" << Inventory[i].count << '\n'
                      << "Max Count :" << Inventory[i].MaxItems << '\n';

            if(!Inventory.empty() && i < Inventory.size())
            {
                Inventory[i].name = "";
                Inventory[i].Durability = 0;
                Inventory[i].count = 0;
                Inventory[i].MaxItems = 0;
                Inventory[i].IDno = 0;
            }
        }
    }
};

void PrintInventory(){

    std::cout << '\n' << "Here are the Items : " << '\n';

    for (int i = 0; i < (int)Inventory.size(); i++){

        // Skip empty slots
        if (Inventory[i].IDno == 0) continue;

        std::cout << Inventory[i].name << '\n';
    }
};

void UploadinventoryToDrive()
{
    std::ofstream file("InventorySystem/InventoryInformation.txt");

    for (int i = 0; i < InventorySize; i++){
        file << Inventory[i].name     << '\n';
        file << Inventory[i].count    << '\n';
        file << Inventory[i].MaxItems << '\n';
        file << Inventory[i].IDno     << '\n';
        file << '\n' << "!#@" << '\n'; // NextLine Identifier
    }
}