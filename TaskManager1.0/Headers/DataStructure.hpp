#pragma once

#include <string>
#include <vector>

#include <nlohmann/json.hpp>

struct Task
{
    //Important
    std::string Name;
    std::string TaskID;

    //Finding
    std::string ParentID;

    //ExtraINFO will be unused for a lot of time
    int CreationData = 0;
    int DeadLine     = 0;

    //Miscellaneous
    std::string Description;

};


struct Container
{
    //Important
    std::string Name;
    std::string ContainerID;

    //storage
    std::string ParentID;

    std::vector<Task> TaskVector;

    //Miscellaneous
    std::string Description;

};

struct Division
{
    //Important
    std::string Name;
    std::string DivisionID;

    //storage
    std::string ParentID;

    std::vector<Container> ContainerVector;
};

struct User
{
    //Important
    std::string UserName;
    std::string UserID;

    std::string UserPassword;
    std::string UserEmail;

    std::vector<Division> DivisionVector;
};

// Defining for JSON

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(Task,      Name, TaskID, ParentID, CreationData, DeadLine, Description)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(Container, Name, ContainerID, ParentID, TaskVector, Description)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(Division,  Name, DivisionID, ParentID, ContainerVector)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(User,      UserName, UserID, UserPassword, UserEmail, DivisionVector)

// BigVector

inline std::vector<User> OnlineUsers;
inline std::vector<User> AllUsers;