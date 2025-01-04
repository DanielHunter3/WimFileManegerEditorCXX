#pragma once

#include <vector>
#include <string>

#include "fmobject.hpp"
#include "communist.hpp"

enum QuantityOfParameters {
    ZERO, ONE, TWO,
    UNDEFINED_ERROR, ARGUMENT_ERROR
};

QuantityOfParameters countParameters(const Function& command, const int8_t& quantityOfParameters) noexcept;

FMObject getFMObject(const std::vector<std::string>& args);