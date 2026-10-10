#pragma once

#include <iostream>
#include <vector>

#include <DataStructure.hpp>

// Return the real object, or nullptr if not found
User*      FindUser      ( const std::string& UserID );
Division*  FindDivision  ( User& Owner,         const std::string& DivisionID  );
Container* FindContainer ( Division& Parent,    const std::string& ContainerID );
Task*      FindTask      ( Container& Parent,   const std::string& TaskID      );