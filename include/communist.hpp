#pragma once

#include <string>

#include "uresult.hpp"

enum Function {
    Cat, Pwd, Rename,
    Copy, Cut, Echo, 
    Perm, Reperm, Ls, 
    Cd, Mkdir, Rmdir, 
    Cls, Rm, Touch,
    Exit
};

 UResult<Function> stringToFunction(const std::string&) noexcept;