// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <map>

#include "communist.hpp"
#include "utildef.hpp"

using enum Function;

UResult<Function> stringToFunction(const std::string& strfunc) noexcept {
  std::map<std::string, Function> map = {
    {"cat", Cat}, {"pwd", Pwd}, {"rename", Rename}, 
    {"cp", Copy}, {"cut", Cut}, {"echo", Echo}, 
    {"chmod", Chmod}, {"ls", Ls}, {"cd", Cd},
    {"mkdir", Mkdir}, {"rmdir", Rmdir}, {"cls", Cls},
    {"rm", Rm}, {"touch", Touch}, {"exit", Exit}
  };
  if (!map.contains(strfunc)) {
    return ResultError(EnumError::RangeOutError, "This command is not supported");
  }
  return map[strfunc];
}

bool validQuantityOfArguments(const Function& func, const int8_t x) noexcept {
  std::map<Function, short> map = {
    {Cat, 1}, {Pwd, 1}, {Rename, 2}, {Copy, 2}, {Cut, 2},
    {Echo, 2}, {Chmod, 2}, {Ls, 0}, {Cd, 1}, {Mkdir, 1},
    {Rmdir, 1}, {Cls, 0}, {Rm, 1}, {Touch, 1}, {Exit, 0}
  };
  return x >= map[func];
}