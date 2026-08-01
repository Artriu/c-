#pragma once

#include <iostream>
#include <string>
#include <vector>

inline size_t FindMaxLength(const std::vector<std::string>& items){
    size_t maxLen = 0;
    for (const auto& s : items)
        if (s.size() > maxLen) maxLen = s.size();
    return maxLen;
}

inline std::string PadToWidth(const std::string& text, size_t width){
    if (text.size() >= width) return text;
    return text + std::string(width - text.size(), ' ');
}

inline void PrintPaddedList(const std::vector<std::string>& items){
    size_t maxLen = FindMaxLength(items);
    for (const auto& s : items)
        std::cout << PadToWidth(s, maxLen) << " <\n";
}
