#include <AddAndRemove.hpp>
#include <DataStructure.hpp>
#include <Search.hpp>

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

void AddDivision(Division DivisionInformation)
{
    // Find the user it belongs to (has to be online)

    User* Owner = FindUser(DivisionInformation.ParentID);

    if ( Owner == nullptr ) {
        std::cout << "User not found for division" << '\n';
        return;
    }

    // ID security

    if ( FindDivision(*Owner, DivisionInformation.DivisionID) != nullptr ) {
        std::cout << "Existing Division ID" << '\n';
        return;
    }

    // All good, add it

    Owner->DivisionVector.push_back(DivisionInformation);
    std::cout << "Added division " << DivisionInformation.Name << '\n';
}


void RemoveDivision(std::string DivisionID, std::string UserID)
{
    // Find the user

    User* Owner = FindUser(UserID);

    if ( Owner == nullptr ) {
        std::cout << "Could not find User" << '\n';
        return;
    }

    // Look for the division and swap it with the last one, then pop
    // (its containers and tasks go with it)

    auto &Divisions = Owner->DivisionVector;

    for ( std::size_t i = 0; i < Divisions.size(); i++ ) {
        if ( Divisions[i].DivisionID == DivisionID ) {

            Divisions[i] = std::move(Divisions.back());
            Divisions.pop_back();

            std::cout << "Removed division " << DivisionID << '\n';
            return;
        }
    }

    std::cout << "Could not find Division" << '\n';
}


// Containers

void AddContainer(Container ContainerInformation, std::string UserID)
{
    // Find the user

    User* Owner = FindUser(UserID);

    if ( Owner == nullptr ) {
        std::cout << "Could not find User" << '\n';
        return;
    }

    // Find the division it goes into

    Division* Parent = FindDivision(*Owner, ContainerInformation.ParentID);

    if ( Parent == nullptr ) {
        std::cout << "Could not find Division" << '\n';
        return;
    }

    // ID security

    if ( FindContainer(*Parent, ContainerInformation.ContainerID) != nullptr ) {
        std::cout << "Existing Container ID" << '\n';
        return;
    }

    // All good, add it

    Parent->ContainerVector.push_back(ContainerInformation);
    std::cout << "Added container " << ContainerInformation.Name << '\n';
}


void RemoveContainer(std::string ContainerID, std::string DivisionID, std::string UserID)
{
    // Find the user

    User* Owner = FindUser(UserID);

    if ( Owner == nullptr ) {
        std::cout << "Could not find User" << '\n';
        return;
    }

    // Find the division it's in

    Division* Parent = FindDivision(*Owner, DivisionID);

    if ( Parent == nullptr ) {
        std::cout << "Could not find Division" << '\n';
        return;
    }

    // Look for the container and swap it with the last one, then pop
    // (its tasks go with it)

    auto &Containers = Parent->ContainerVector;

    for ( std::size_t i = 0; i < Containers.size(); i++ ) {
        if ( Containers[i].ContainerID == ContainerID ) {

            Containers[i] = std::move(Containers.back());
            Containers.pop_back();

            std::cout << "Removed container " << ContainerID << '\n';
            return;
        }
    }

    std::cout << "Could not find Container" << '\n';
}


// Tasks

void AddTask(Task TaskInformation, std::string UserID, std::string DivisionID)
{
    // Find the user

    User* Owner = FindUser(UserID);

    if ( Owner == nullptr ) {
        std::cout << "Could not find User" << '\n';
        return;
    }

    // Find the division

    Division* Div = FindDivision(*Owner, DivisionID);

    if ( Div == nullptr ) {
        std::cout << "Could not find Division" << '\n';
        return;
    }

    // Find the container it goes into

    Container* Parent = FindContainer(*Div, TaskInformation.ParentID);

    if ( Parent == nullptr ) {
        std::cout << "Could not find Container" << '\n';
        return;
    }

    // ID security

    if ( FindTask(*Parent, TaskInformation.TaskID) != nullptr ) {
        std::cout << "Existing Task ID" << '\n';
        return;
    }

    // All good, add it

    Parent->TaskVector.push_back(TaskInformation);
    std::cout << "Added task " << TaskInformation.Name << '\n';
}


void RemoveTask(std::string TaskID, std::string ContainerID, std::string DivisionID, std::string UserID)
{
    // Find the user

    User* Owner = FindUser(UserID);

    if ( Owner == nullptr ) {
        std::cout << "Could not find User" << '\n';
        return;
    }

    // Find the division

    Division* Div = FindDivision(*Owner, DivisionID);

    if ( Div == nullptr ) {
        std::cout << "Could not find Division" << '\n';
        return;
    }

    // Find the container it's in

    Container* Parent = FindContainer(*Div, ContainerID);

    if ( Parent == nullptr ) {
        std::cout << "Could not find Container" << '\n';
        return;
    }

    // Look for the task and swap it with the last one, then pop

    auto &Tasks = Parent->TaskVector;

    for ( std::size_t i = 0; i < Tasks.size(); i++ ) {
        if ( Tasks[i].TaskID == TaskID ) {

            Tasks[i] = std::move(Tasks.back());
            Tasks.pop_back();

            std::cout << "Removed task " << TaskID << '\n';
            return;
        }
    }

    std::cout << "Could not find Task" << '\n';
}
