#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>

struct item{

    // Constants
    std::string name;
    int IDno;

    // Editable
    int count;
    int MaxItems;

    // Optional
    std::string ExpiryDate;
};

// Globals

std::vector<item> Inventory;
int InventorySize = 30;

// Function Declations

void AddItem(std::string TakenName, int TakenCount, int TakenMaxItems, int TakenIDno, std::string TakenExpiry);
void RemoveItem(int IDno);
void PrintInventory();
void UploadinventoryToDrive();
void LoadInventoryFromDrive();

int main(){

    // Give the vector its 30 empty slots (all fields zeroed)
    Inventory.resize(InventorySize);

    int choice = 0;

    while (choice != 6){

        system("cls");   // clear the console each pass

        // Menu
        std::cout << '\n'
                  << "1. Add Item"        << '\n'
                  << "2. Remove Item"     << '\n'
                  << "3. Print Inventory" << '\n'
                  << "4. Upload to Drive" << '\n'
                  << "5. Load from Drive" << '\n'
                  << "6. Quit"            << '\n'
                  << "Choice : ";

        std::cin >> choice;

        if (choice == 1){
            std::string name, expiry;
            int count, maxItems, IDno;

            std::cout << "Name      : ";
            std::cin  >> name;
            std::cout << "Count     : ";
            std::cin  >> count;
            std::cout << "Max Count : ";
            std::cin  >> maxItems;
            std::cout << "ID Number : ";
            std::cin  >> IDno;
            std::cout << "Expiry    : ";
            std::cin  >> expiry;

            AddItem(name, count, maxItems, IDno, expiry);
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
        else if (choice == 4){
            UploadinventoryToDrive();
        }
        else if (choice == 5){
            LoadInventoryFromDrive();
        }

        // Pause so the result stays on screen until Enter
        if (choice != 6){
            std::cout << "\nPress Enter to continue...";
            std::cin.ignore();
            std::cin.get();
        }
    }

    return 0;
}

// Function Initialisation

void AddItem(std::string TakenName, int TakenCount, int TakenMaxItems, int TakenIDno, std::string TakenExpiry){

    // Guard: ID must land inside the vector
    if (TakenIDno <= 0 || TakenIDno >= InventorySize){
        std::cout << "Invalid ID Number" << '\n';
        return;
    }

    // Empty slot = space to place the item

    if (Inventory[TakenIDno].IDno == 0) {
        std::cout << "Space Available" << '\n';
        Inventory[TakenIDno].name       = TakenName;
        Inventory[TakenIDno].count      = TakenCount;
        Inventory[TakenIDno].MaxItems   = TakenMaxItems;
        Inventory[TakenIDno].IDno       = TakenIDno;
        Inventory[TakenIDno].ExpiryDate = TakenExpiry;
        return;
    }
    else{
        std::cout << "Filled Slot" << '\n';

        char Replace;

        std::cout << "Replace Slot?" << '\n';
        std::cin >> Replace;

        if (Replace == 'Y' || Replace == 'y'){
            Inventory[TakenIDno].name       = TakenName;
            Inventory[TakenIDno].count      = TakenCount;
            Inventory[TakenIDno].MaxItems   = TakenMaxItems;
            Inventory[TakenIDno].IDno       = TakenIDno;
            Inventory[TakenIDno].ExpiryDate = TakenExpiry;
        }
    }
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
                Inventory[i].ExpiryDate = "";
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

        std::cout << Inventory[i].name
                  << "  (x" << Inventory[i].count << ")"
                  << "  Expires: " << Inventory[i].ExpiryDate << '\n';
    }
};

void UploadinventoryToDrive()
{
    std::ofstream file("InventoryInformation.txt");

    // Check once before writing
    if (!file.is_open()) {
        std::cout << '\n' << "Failed To Upload" << '\n';
        return;
    }

    for (int i = 1; i < InventorySize; i++){

        // Skip empty slots
        if (Inventory[i].IDno == 0) continue;

        file << Inventory[i].name       << '\n';
        file << Inventory[i].count      << '\n';
        file << Inventory[i].MaxItems   << '\n';
        file << Inventory[i].IDno       << '\n';
        file << Inventory[i].ExpiryDate << '\n';
    }

    std::cout << '\n' << "Uploaded!" << '\n';
}

void LoadInventoryFromDrive(){
    std::ifstream file("InventoryInformation.txt");

    // Check the file opened
    if (!file.is_open()) {
        std::cout << '\n' << "Failed To Load" << '\n';
        return;
    }

    std::string name, expiry;
    int count, maxItems, IDno;

    // Read one item block per pass; loop ends at end-of-file
    while (file >> name >> count >> maxItems >> IDno >> expiry){

        // Guard: only place if the ID is a valid slot
        if (IDno > 0 && IDno < InventorySize){
            Inventory[IDno].name       = name;
            Inventory[IDno].count      = count;
            Inventory[IDno].MaxItems   = maxItems;
            Inventory[IDno].IDno       = IDno;
            Inventory[IDno].ExpiryDate = expiry;
        }
    }

    std::cout << '\n' << "Loaded!" << '\n';
}