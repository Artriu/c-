#include <AddAndRemove.hpp>

//User

void AddUser(User UserInfo){
    for (std::string c : UserEmails){
        if (c == UserInfo.UserID){
            std::cout << "Email in use " << c << '\n';
        };
    };

    // Comparison of IDs for checking properID creation, will be removed

    for (std::string c : UserIDs){
        if (c == UserInfo.UserID){
            std::cout << "Error : Fix the ID assignment Dumbass";
        }
    }

    UserIDs.push_back(UserInfo.UserID);
    UserEmails.push_back(UserInfo.UserEmail);
    UserPasswords.push_back(UserInfo.UserPassword);

    // Test

    std::cout << "Emails of the Users" << '\n';
    for (std::string c : UserEmails) {
        std::cout << c << '\n';
    };
};


void RemoveUser(std::string UserID, std::string UserPassword){
    for (std::string c : UserIDs) {
        if ( c == UserID ) {
            std::cout << "Found User" << '\n';

            // Delete the User and the Divions, Containers and Tasks
            break;
        }

        std::cout << "Could not find user";
    }
};