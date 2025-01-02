// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <iostream>

#include "header/fmobject.hpp"

int main(void) {
    std::vector<std::string> args;
    std::string s;
    FMCommand command(s);
    std::cout << typeToString(command.setType());
}