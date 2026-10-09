//Headers

#include <DataStructure.hpp>
#include <Search.hpp>
#include <AddAndRemove.hpp>

//Test Users

#include <TestData.hpp>

//Includes

#include <iostream>
#include <vector>

#include <sqlite3.h>

int main(){
    std::cout << "--- File Start ---" << '\n';
    //Sample User

    MakeDummyUsers(5);
    MakeTrickyUsers();

    //stuff

    std::cout << "Deleting User 4" << '\n';

    RemoveUser(AllUsers[4].UserID, AllUsers[4].UserPassword);

    std::cout << "Remaining Users email" << '\n';

    for (auto c : AllUsers)
    {
        std::cout << c.UserEmail << '\n';
    }
    std::cout << "--- File End ---";

    return 0;
};