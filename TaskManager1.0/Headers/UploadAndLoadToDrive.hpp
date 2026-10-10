#pragma once

// Headers

#include <string>
#include <fstream>

#include <nlohmann/json.hpp>
#include <DataStructure.hpp>

// Defining

int GetSector(std::string UserID);
int loadSector(int Sector, std::string UserID, std::string UserPassword);
bool saveSector(int Sector);