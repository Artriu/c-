// Answer to MenuLoop.cpp -- only open this after you have your own version running.

#include <iostream>
#include <string>
#include <vector>

// Returns true and writes to 'out' only if the whole line is a valid number.
bool LineToInt(const std::string& line, int& out) {
    if (line.empty()) return false;

    size_t start = 0;
    bool negative = false;
    if (line[0] == '-') { negative = true; start = 1; }
    if (start == line.size()) return false;

    int value = 0;
    for (size_t i = start; i < line.size(); i++) {
        if (!std::isdigit(static_cast<unsigned char>(line[i]))) return false;
        value = value * 10 + (line[i] - '0');
    }

    out = negative ? -value : value;
    return true;
}

void PrintMenu() {
    std::cout << "\n1) Add a task\n"
              << "2) List tasks\n"
              << "0) Quit\n"
              << "> ";
}

int main() {
    std::vector<std::string> titles;

    while (true) {
        PrintMenu();

        std::string line;
        if (!std::getline(std::cin, line)) break; // stream closed

        int choice = 0;
        if (!LineToInt(line, choice)) {
            std::cout << "Invalid input\n";
            continue;
        }

        switch (choice) {
        case 1: {
            std::cout << "Title: ";
            std::string title;
            std::getline(std::cin, title);
            titles.push_back(title);
            break;
        }
        case 2:
            if (titles.empty()) {
                std::cout << "No tasks yet.\n";
                break;
            }
            for (size_t i = 0; i < titles.size(); i++)
                std::cout << i + 1 << ") " << titles[i] << '\n';
            break;

        case 0:
            return 0;

        default:
            std::cout << "Unknown option\n";
            break;
        }
    }

    return 0;
}
