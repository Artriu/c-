// Headers

#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>

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

std::string SectorPath(int Sector){

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
    return CompleteStringAddress;
}

int loadSector (int Sector, std::string UserID, std::string UserPassword) 
{

    // Loading to online

    std::string CompleteStringAddress = SectorPath(Sector);

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

bool saveSector(int Sector, std::string UserID){

    // Find the user in RAM

    User* Me = FindUser(UserID);

    if ( Me == nullptr ) {
        std::cout << "User not online, nothing to save" << '\n';
        return false;
    }

    // Make sure the Sectors folder exists

    std::string CompleteStringAddress = SectorPath(Sector);

    std::filesystem::create_directories("Sectors");

    // Read the sector fresh from disk, so other users in it keep their latest data
    // (no file yet = empty list)

    json WholeSector = json::array();

    std::ifstream File(CompleteStringAddress);

    if ( File ) {
        try {
            WholeSector = json::parse(File);
        }
        catch (const std::exception &c) {
            std::cout << "Sector file is broken, not saving over it" << '\n';
            return false;
        }
    }

    File.close();

    // Swap in this user (or add them if they're not in the file yet)

    bool Found = false;

    for ( auto& UserJSON : WholeSector )
    {
        if ( UserJSON["UserID"] == UserID )
        {
            UserJSON = *Me;
            Found = true;
            break;
        }
    }

    if ( !Found ) {
        WholeSector.push_back(*Me);
    }

    // Write to a .tmp file first, then swap it in
    // (if the program dies mid-write, the real file is still the old good one)

    std::string TempAddress = CompleteStringAddress + ".tmp";

    std::ofstream Out(TempAddress);
    Out << WholeSector.dump(2);
    Out.close();

    if ( !Out ) {
        std::cout << "Could not write the sector" << '\n';
        return false;
    }

    std::filesystem::rename(TempAddress, CompleteStringAddress);

    return true;
}