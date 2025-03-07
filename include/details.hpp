#pragma once

#include <algorithm>

template <typename T, typename E>
bool in(const T& container, const E& value) noexcept {
    return std::find(container.begin(), container.end(), value) != container.end();
}