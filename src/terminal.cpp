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
    if (tokens.size() == 0) {
        throw std::invalid_argument("The command line is empty");
    }

    std::string command = tokens.at(0);
    if (!isValidFunction(command)) {
        throw std::invalid_argument("Invalid command (getTerminal)");
    }
    int8_t quantityOfParameters = tokens.size() - 1;

    const std::array<std::string, 1> systemCommands { "exit" };
    const std::array<std::string, 5> directoryCommands { "cd", "mkdir", "rmdir", "ls", "cls" };
    const std::array<std::string, 10> fileCommands { "touch", "rm", "cat", 
                                                    "echo", "rename", "cp", 
                                                    "perm", "repem", "cut",
                                                    "pwd" };

    // if (in(systemCommands, command)) {
    //     if (command == "exit") {
    //         return false;
    //     }
    // }
    // if (in(directoryCommands, command)) {
    //     for (const auto& i: directoryUserCommand(tokens, command, quantityOfParameters)){
    //         std::cout << i << std::endl;
    //     }
    // }
    // else if (in(fileCommands, command)) {
    //     std::cout << fileUserCommand(tokens, command, quantityOfParameters);
    // }
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