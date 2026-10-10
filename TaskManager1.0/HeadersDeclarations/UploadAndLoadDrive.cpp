// Headers

#include <iostream>
#include <vector>
#include <fstream>

#include <nlohmann/json.hpp>

#include <UploadAndLoadToDrive.hpp>
#include <DataStructure.hpp>
#include <Search.hpp>

// Namespace

using json = nlohmann::json;

int GetSector(std::string UserID)
{
    if ( UserID.length() < 3) { return -1; }
    
    try 
    {
        // Getting the underscore position in the string
        size_t lastposition = UserID.rfind("_");

        if (lastposition == std::string::npos) { std::cout << "Invalid ID\n"; return -1; }

        // Getting the sector
        int sector = std::stoi(UserID.substr(lastposition + 1, 3));

        if (sector < 1 || sector > 10) { std::cout << "Invalid Sector" << '\n'; return -1; }
            
        std::cout << "Valid Sector : " << sector << '\n';
        return sector;
    }
    catch (const std::exception &c) {}
    std::cout << "Invalid Data" << '\n'; 
    return -1;
}

int loadSector (int Sector, std::string UserID, std::string UserPassword) 
{

    // Getting the file name
    std::string SectorString = std::to_string(Sector);

    int size = SectorString.size();

    switch (size)
    {
    case 1:
        SectorString.insert(0, "00");
        break;
    
    case 2:
        SectorString.insert(0, "0");
        break;

    default:
        break;
    }

    std::string CompleteStringAddress = "Sectors/Sector" + SectorString + ".json";

    // Loading to online

    std::ifstream File(CompleteStringAddress);

    if (!File) return -1;

    try{
        json WholeSector = json::parse(File);

        for ( auto& UserJSON : WholeSector )
        {
            if ( UserJSON["UserID"] == UserID && UserJSON["UserPassword"] == UserPassword )
            {
                if ( FindUser(UserID) != nullptr ) return -2;

                OnlineUsers.push_back( UserJSON.get<User>() );

                return 0;
            }
        }
        return -3;
    }

    catch (const std::exception &c) {}
    return -4;
}