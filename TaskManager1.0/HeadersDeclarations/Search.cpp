#include "Search.hpp"

// Important one, basically the whole thing

bool FindUserAndLoadToOnline ( std::string UserID, std::string UserPassword ) {

    // Preventing Bad ID
    if ( UserID.length() < 3) { return false; }
    
    try 
    {
        // Getting the underscore position in the string
        size_t lastposition = UserID.rfind("_");

        if (lastposition == std::string::npos) { std::cout << "Invalid ID\n"; return false; }

        // Getting the sector
        int sector = std::stoi(UserID.substr(lastposition + 1));

        if (sector < 1 || sector > 100) { std::cout << "Invalid Sector" << '\n'; }
            
        std::cout << "Valid Sector : " << sector << '\n';
            
        // Switch it to looking throught the "UploadAndLoadToDrive.hpp" header
            
        for ( User &c : AllUsers )
        {
            if ( c.UserID == UserID && c.UserPassword == UserPassword ) 
            {
                // Check for multiple Users
                for ( auto t : OnlineUsers) 
                {
                    if ( t.UserID == UserID) 
                    {
                        std::cout << "Already logged in" << '\n';
                        return false;
                    }
                }

                OnlineUsers.push_back(c);
                return true; 
            }
        }
        std::cout << "could not find user" << '\n';
        return false;

    }
    catch (const std::exception &c) {}
    
    std::cout << "Invalid Data" << '\n';
    return false;
}

// Helpers

User* FindUser ( const std::string& UserID ) {
    for ( auto &c : OnlineUsers ) {
        if ( c.UserID == UserID ) return &c;
    }
    return nullptr;
}

Division* FindDivision ( User& Owner, const std::string& DivisionID ) {
    for ( auto &d : Owner.DivisionVector ) {
        if ( d.DivisionID == DivisionID ) return &d;
    }
    return nullptr;
}

Container* FindContainer ( Division& Parent, const std::string& ContainerID ) {
    for ( auto &c : Parent.ContainerVector ) {
        if ( c.ContainerID == ContainerID ) return &c;
    }
    return nullptr;
}

Task* FindTask ( Container& Parent, const std::string& TaskID ) {
    for ( auto &t : Parent.TaskVector ) {
        if ( t.TaskID == TaskID ) return &t;
    }
    return nullptr;
}
