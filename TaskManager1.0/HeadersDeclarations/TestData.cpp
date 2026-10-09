#include <TestData.hpp>
#include <AddAndRemove.hpp>
#include <DataStructure.hpp>

#include <string>
#include <algorithm>

void MakeDummyUsers(int Count){
    for (int i = 1; i <= Count; i++){
        std::string Number = std::to_string(i);

        User Dummy;
        Dummy.UserName     = "Dummy" + Number;
        Dummy.UserID       = "DUMMY" + std::string(4 - std::min<int>(4, Number.size()), '0') + Number;   // DUMMY0001, DUMMY0002...
        Dummy.UserEmail    = "dummy" + Number + "@test.com";
        Dummy.UserPassword = "pass" + Number;

        AddUser(Dummy);
    }
}

void MakeTrickyUsers(){
    // Same email as Dummy1, different ID -> should say "Email in use" and NOT be added
    User SameEmail;
    SameEmail.UserName     = "EmailThief";
    SameEmail.UserID       = "TRICK0001";
    SameEmail.UserEmail    = "dummy1@test.com";
    SameEmail.UserPassword = "steal";
    AddUser(SameEmail);

    // Same ID as Dummy2, different email -> should be caught by the ID check and NOT be added
    User SameID;
    SameID.UserName     = "IDClone";
    SameID.UserID       = "DUMMY0002";
    SameID.UserEmail    = "clone@test.com";
    SameID.UserPassword = "clone";
    AddUser(SameID);

    // Totally normal user -> should be added fine
    User Normal;
    Normal.UserName     = "Normal";
    Normal.UserID       = "TRICK0003";
    Normal.UserEmail    = "normal@test.com";
    Normal.UserPassword = "normal";
    AddUser(Normal);
}
