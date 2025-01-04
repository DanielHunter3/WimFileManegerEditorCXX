#pragma once

#include <string>

enum Function {
    Cat, Pwd, Rename,
    Copy, Cut, Echo, 
    Perm, Reperm, Ls, 
    Cd, Mkdir, Rmdir, 
    Cls, Rm, Touch,
    Exit
};

bool isValidFunction(const Function& aCommand) noexcept;

Function stringToFunction(const std::string&);