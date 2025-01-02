#pragma once

#include <vector>
#include <string>

enum QuantityOfParameters {
    ZERO, ONE, TWO, THREE,
    ERROR
};

QuantityOfParameters countParameters(const std::string& command, const int8_t& quantityOfParameters);

auto f(const std::vector<std::string>& args);