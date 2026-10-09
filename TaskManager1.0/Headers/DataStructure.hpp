#pragma once

#include <string>
#include <vector>

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

// BigVector

inline std::vector<User> OnlineUsers;
inline std::vector<User> AllUsers;