// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <cstdint>
#include <array>
#include <iostream>
#include <sstream>

#include "header/usercommand.hpp"
#include "header/communist.hpp"
#include "header/filemaneger.hpp"
#include "header/terminal.hpp"

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
    std::cout << getCurrentWorkingDirectory() << "> ";
    std::getline(std::cin, command);
    return getCommand(command);
}

bool getTerminal(const std::vector<std::string>& tokens) {
    // TODO: false for "exit"
    if (tokens.at(0) == "exit") {
        return false;
    }
    FMObject object(getFMObject(tokens));
    std::cout << object.toTerminal() << std::endl;
    return true;
}

void terminal() {
    while (true)
    {
        try {
            if (!getTerminal(setTerminal())) { break; }
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << '\n';
        }
    }
}