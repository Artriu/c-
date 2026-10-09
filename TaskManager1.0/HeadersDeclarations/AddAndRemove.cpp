#include <AddAndRemove.hpp>
#include <DataStructure.hpp>

// User

void AddUser(User UserInfo){
    bool Failure = false;

    for (auto c : AllUsers){
        if (c.UserEmail == UserInfo.UserEmail){
            std::cout << "Email in use " << c.UserEmail << '\n';
            Failure = true;
        };
    };

    // Comparison of IDs for checking properID creation, will be removed

    for (auto c : AllUsers){
        if (c.UserID == UserInfo.UserID){
            std::cout << "Error : Fix the ID assignment Dumbass" << '\n';
            Failure = true;
        }
    }


    if (Failure == false){
        AllUsers.push_back(UserInfo);
    }

};


void RemoveUser(std::string UserID, std::string UserPassword){
    for (int i = 0; i < AllUsers.size(); i++) {
        if ( AllUsers[i].UserID == UserID && AllUsers[i].UserPassword == UserPassword) {
            std::cout << "Found User" << '\n';

            AllUsers[i] = std::move(AllUsers.back());
            AllUsers.pop_back();

            // Delete the Divisions, Containers and tasks
            return;
        }
    }

    std::cout << "Did not find user" << '\n';
};

// Divisions

void AddDivision(Division DivisionInformation){

    for (int c = 0; c < AllUsers.size(); c++)
    {
        if ( AllUsers[c].UserID == DivisionInformation.ParentID )
        {
            // ID security

            for ( auto t : AllUsers[c].DivisionVector )
            {
                if ( t.DivisionID == DivisionInformation.DivisionID)
                {
                    std::cout << "Existing Division ID" << '\n';
                    return;
                }
            }

            std::cout << "User Found for division " << DivisionInformation.Name << '\n';
            AllUsers[c].DivisionVector.push_back(DivisionInformation);
            return;
        }
    }

    std::cout << "User Not found for division" << '\n';
}

void RemoveDivision(std::string DivisionID, std::string ParentID)
{
    for ( auto &c : AllUsers ) {
        if ( ParentID == c.UserID ) {
            std::cout << "User Containing the division found" << '\n';

            for ( int t = 0; t < c.DivisionVector.size(); t++) {
                if ( c.DivisionVector[t].DivisionID == DivisionID )
                {
                    std::cout << "Division found in user" << '\n';
                    c.DivisionVector[t] = std::move(c.DivisionVector.back());
                    c.DivisionVector.pop_back();

                    return;
                }
            }
            std::cout << "Could not find Division";
            return;

        }
    }
    std::cout << "Could not find User";
}