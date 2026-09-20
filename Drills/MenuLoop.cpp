// Drill: MenuLoop
// Goal: a menu that loops until the user quits, and never breaks on bad input.
//
// Requirements:
//  1. Print a numbered menu:
//        1) Add a task
//        2) List tasks
//        0) Quit
//  2. Read the user's answer as a WHOLE LINE (not with std::cin >> x).
//  3. Turn that line into an int yourself. If the line is not a valid number,
//     print "Invalid input" and show the menu again -- do not crash, do not exit.
//  4. switch on the number:
//        1 -> ask for a title (a whole line again), store it in a vector<string>
//        2 -> print every stored title, numbered from 1
//        0 -> leave the loop and return 0
//        anything else -> "Unknown option"
//  5. Listing when nothing is stored prints "No tasks yet."
//
// Rules: no globals, everything lives inside main() or small helpers above it.

#include <iostream>
#include <string>
#include <vector>

int main() {
    // your code here
    return 0;
}
