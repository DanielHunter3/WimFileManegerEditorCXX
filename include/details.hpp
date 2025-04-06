#pragma once

#include <algorithm>
#include <vector>

#include "uresult.hpp"

template <typename T, typename E>
bool in(const T& container, const E& value) noexcept {
    return std::find(container.begin(), container.end(), value) != container.end();
}

UResult<std::vector<std::string>> split(const std::string &txt, char ch)
{
    if (!in(txt, ch)) {
        return StructError {EnumError::DataFoundError, "Просто нет такого символа"};
    }
    size_t pos = txt.find(ch);
    unsigned initialPos = 0;
    std::vector<std::string> strs;

    // Decompose statement
    while(pos != std::string::npos) {
        strs.emplace_back(txt.substr(initialPos, pos - initialPos));
        initialPos = pos + 1;

        pos = txt.find(ch, initialPos);
    }

    // Add the last one
    strs.emplace_back(txt.substr(initialPos, std::min(pos, txt.size()) - initialPos + 1));

    return strs;
}