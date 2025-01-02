#pragma once

#include <functional>
#include <string>

#include "filemaneger.hpp"

// Define a type for the command functions
using StringFunction = std::function<std::string()>;
using VectorStringFunction = std::function<std::vector<std::string>()>;

enum EnumVariantFunction {
    StrFunc,
    VoidFunc,
    VecStrFunc
};

StringFunction getElementFunction(const std::vector<std::string>& arguments);

StringFunction getFunctionOfFile(const std::vector<std::string>& arguments);

VectorStringFunction getFunctionOfDirectoryVector(const std::vector<std::string>& arguments);

StringFunction getFunctionOfDirectoryString(const std::vector<std::string>& arguments);

StringFunction getStringUniversalFunction(const std::vector<std::string>& arguments);