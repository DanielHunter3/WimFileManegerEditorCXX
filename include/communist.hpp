#pragma once

#include <string>
#include <cstdint>

#include "uresult.hpp"

enum class Function {
  Cat, Pwd, Rename,
  Copy, Cut, Echo, 
  Chmod, Ls, Cd, 
  Mkdir, Rmdir, Cls, 
  Rm, Touch, Exit
};

UResult<Function> stringToFunction(const std::string&) noexcept;
bool validQuantityOfArguments(const Function& func, int8_t x) noexcept;