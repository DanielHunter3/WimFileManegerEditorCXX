#pragma once

#include <functional>
#include <string>
#include <variant>

#include "filemaneger.hpp"

// Define a type for the command functions
using StringFunction = std::function<std::string()>;
using VectorStringFunction = std::function<std::vector<std::string>()>;
using VoidFunction = std::function<void()>;

enum EnumVariantFunction {
    StrFunc,
    VoidFunc,
    VecStrFunc
};

StringFunction getElementFunction(const std::vector<std::string>& arguments);

StringFunction getFunctionOfFile(const std::vector<std::string>& arguments);

VectorStringFunction getFunctionOfDirectoryVector(const std::vector<std::string>& arguments);

VoidFunction getFunctionOfDirectoryVoid(const std::vector<std::string>& arguments);

// Все функции, кроме getFunctionOfDirectoryVector
StringFunction getStringUniversalFunction(const std::vector<std::string>& arguments);