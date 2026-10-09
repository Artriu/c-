#pragma once

// Fake accounts for testing AddUser / RemoveUser. Delete this file + TestData.cpp when you're done testing.

// Adds Count normal users: Dummy1 ... DummyN  (IDs DUMMY0001..., emails dummy1@test.com...)
void MakeDummyUsers(int Count);

// Adds a few users that SHOULD be rejected - duplicate email, duplicate ID.
// Call it after MakeDummyUsers so there's something to clash with.
void MakeTrickyUsers();
