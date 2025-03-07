// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <map>

#include "communist.hpp"

Result<Function> stringToFunction(const std::string& strfunc) noexcept {
    std::map<std::string, Function> map = {
        {"cat", Cat}, {"pwd", Pwd}, {"rename", Rename}, 
        {"cp", Copy}, {"cut", Cut}, {"echo", Echo},
        {"perm", Perm}, {"reperm", Reperm}, {"ls", Ls}, 
        {"cd", Cd}, {"mkdir", Mkdir}, {"rmdir", Rmdir}, 
        {"cls", Cls}, {"rm", Rm}, {"touch", Touch},
        {"exit", Exit}
    };
    if (map.find(strfunc) == map.end()) {
        return ResultError {RangeOutError, "This command is not supported"};
    }
    return map[strfunc];
}