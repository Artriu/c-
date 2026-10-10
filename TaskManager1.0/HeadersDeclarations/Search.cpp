#include "Search.hpp"
#include "UploadAndLoadToDrive.hpp"

// Helpers

User* FindUser ( const std::string& UserID ) {
    for ( auto &c : OnlineUsers ) {
        if ( c.UserID == UserID ) return &c;
    }
    return nullptr;
}

Division* FindDivision ( User& Owner, const std::string& DivisionID ) {
    for ( auto &d : Owner.DivisionVector ) {
        if ( d.DivisionID == DivisionID ) return &d;
    }
    return nullptr;
}

Container* FindContainer ( Division& Parent, const std::string& ContainerID ) {
    for ( auto &c : Parent.ContainerVector ) {
        if ( c.ContainerID == ContainerID ) return &c;
    }
    return nullptr;
}

Task* FindTask ( Container& Parent, const std::string& TaskID ) {
    for ( auto &t : Parent.TaskVector ) {
        if ( t.TaskID == TaskID ) return &t;
    }
    return nullptr;
}
