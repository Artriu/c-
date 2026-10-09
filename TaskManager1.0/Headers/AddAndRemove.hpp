#pragma once

#include <iostream>
#include <vector>

#include <DataStructure.hpp>

void AddTask(Task TaskInformation);
void RemoveTask(std::string TaskID);

void AddContainer(Container ContainerInformation);
void RemoveContainer(std::string ContainerID);

void AddDivision(Division DivisionInformation);
void RemoveDivision(std::string DivisionID, std::string ParentID);

void AddUser(User UserInfo);
void RemoveUser(std::string UserID, std::string UserPassword);