#pragma once

#include <iostream>
#include <vector>

#include <DataStructure.hpp>

// The user has to be online. ParentID of the thing being added = the ID of the level above it.

void AddTask(Task TaskInformation, std::string UserID, std::string DivisionID);
void RemoveTask(std::string TaskID, std::string ContainerID, std::string DivisionID, std::string UserID);

void AddContainer(Container ContainerInformation, std::string UserID);
void RemoveContainer(std::string ContainerID, std::string DivisionID, std::string UserID);

void AddDivision(Division DivisionInformation);
void RemoveDivision(std::string DivisionID, std::string UserID);

void AddUser(User UserInfo);
void RemoveUser(std::string UserID, std::string UserPassword);