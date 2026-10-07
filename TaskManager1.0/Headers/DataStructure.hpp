#pragma once

#include <iostream>
#include <vector>

struct Task
{
    //Important
    std::string Name;
    std::string TaskID;

    //Finding
    std::string ParentID;

    //ExtraINFO will be unused for a lot of time
    int CreationData;
    int DeadLine;

    //Miscellaneous
    std::string Description;

};


struct Container
{
    //Important
    std::string Name;
    std::string ContainerID;

    std::vector<Task> ContainerVector;

    //Miscellaneous
    std::string Description;

};

struct Division
{
    //Important
    std::string Name;
    std::string ContainerID;

    std::vector<Container> DivisionVector;
};

struct User
{
    //Important
    std::string UserName;
    std::string UserID;

    std::string UserPassword;
    std::string UserEmail;

    std::vector<Division> UserVector;
};

// DoD design for Users

std::vector<std::string> UserIDs;        // |                                                                                                 |
std::vector<std::string> UserEmails;     // | The stuff should be aligned, The email & password at position 12 should belong to the same user |
std::vector<std::string> UserPasswords;  // |                                                                                                 |