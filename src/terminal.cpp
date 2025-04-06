// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <cstdint>
#include <array>
#include <iostream>
#include <sstream>

#include "usercommand.hpp"
#include "communist.hpp"
#include "terminal.hpp"
#include "element.hpp"

std::vector<std::string> getCommand(std::string& command) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(command);
    while (std::getline(tokenStream, token, ' ')) {
        tokens.push_back(token);
    }
    return tokens;
}

std::vector<std::string> setTerminal() {
    std::string command;
    std::cout << filemaneger::directory::getCurrentWorkingDirectory() << "> ";
    std::getline(std::cin, command);
    return getCommand(command);
}

UResult<bool> getTerminal(const std::vector<std::string>& tokens) noexcept {
    if (tokens.empty()) {
        return StructError {EnumError::EmptyCommandError, "No command specified!"};
    }
    auto t = getFMObject(tokens);
    if (t.is_error()) {
        if (t.error().type() == EnumError::ExitCommandError) return false;
        else return t.error();
    }
    FMObject object(*t);
    std::cout << object.toTerminal() << '\n';
    return true;
}

void terminal() {
    while (true)
    {
        auto t = getTerminal(setTerminal());
        if (t.is_error()) {
            std::cerr << "Error: " << t.error().message() << '\n';
            continue;
        }
        if (!*t) {
            break;
        }
    }
}