//Headers

#include <DataStructure.hpp>
#include <search.hpp>
#include <AddAndRemove.hpp>

//Includes

#include <iostream>
#include <vector>

#include <sqlite3.h>

int main(){
    //Sample User

    User Guest1;
    Guest1.UserName = "Guest1";
    Guest1.UserID = "ABCD1234";
    Guest1.UserPassword = "BobTheCat";
    Guest1.UserEmail = "xyz123@gmail.com";

    //stuff

    AddUser(Guest1);
};