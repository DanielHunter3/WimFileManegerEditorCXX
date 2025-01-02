// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <memory>
#include <array>

#include "header/details.hpp"
#include "header/communist.hpp"

bool isValidFunction(std::string& aCommand) {
    auto allCommands = std::make_unique<std::array<std::string, 15>>();
    *allCommands = {
        "cat", "pwd", "rename", "cp", "cut" "echo", "perm", 
        "repem", "ls", "cd", "mkdir", "rmdir", "cls", "exit"
    };
    if (in(*allCommands, aCommand)) {
        return true;
    }
    return false;
}