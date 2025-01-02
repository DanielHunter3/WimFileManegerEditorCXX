// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <map>
#include <cstdlib>
#include <memory>

#include "header/element.hpp"
#include "header/funcptr.hpp"

using namespace filemaneger;

StringFunction getElementFunction(const std::vector<std::string>& arguments) {
    auto functions = std::make_unique<std::map<std::string, StringFunction>>();
    *functions = {
        {"rename", [arguments]() {
            element::rename(arguments.at(1), arguments.at(2));
            return "\0";
        }},
        {"copy", [arguments]() {
            element::copy(arguments.at(1), arguments.at(2));
            return "\0";
        }},
        {"pwd", [arguments]() {
            return element::pwd(arguments.at(1));
        }}
    };
    return functions->at(arguments.at(0));
}

StringFunction getFunctionOfFile(const std::vector<std::string>& arguments) {
    auto functions = std::make_unique<std::map<std::string, StringFunction>>();
    *functions = {
        {"cat", [arguments]() {
            return filemaneger::file::readFile(arguments.at(1));
        }},
        {"echo", [arguments]() {
            file::writeFile(arguments.at(1), arguments.at(2));
            return "\0";
        }},
        {"touch", [arguments](){
            file::createFile(arguments.at(1));
            return "\0";
        }},
        {"rm", [arguments](){
            file::deleteFile(arguments.at(1));
            return "\0";
        }}
    };
    return functions->at(arguments.at(0));
}

VectorStringFunction getFunctionOfDirectoryVector(const std::vector<std::string>& arguments) 
{
    auto functions = std::make_unique<std::map<std::string, VectorStringFunction>>(); 
    *functions = {
        {"ls", [arguments]() {
            return getFilesAndDirectories(arguments.at(1));
        }},
        {"cd", [arguments]() {
            directory::changeDirectory(arguments.at(1));
            return getFilesAndDirectories(arguments.at(1));
        }},
    };
    return functions->at(arguments.at(0));
}

VoidFunction getFunctionOfDirectoryVoid(const std::vector<std::string>& arguments) 
{
    auto functions = std::make_unique<std::map<std::string, VoidFunction>>(); 
    *functions = {
        {"mkdir", [arguments]() { directory::createDirectory(arguments.at(1)); }},
        {"rmdir", [arguments]() { directory::deleteDirectory(arguments.at(1)); }},
        {"cls", []() {
            #ifdef _WIN32
                std::system("cls");
            #else
                std::system("clear");
            #endif
        }}
    };
    return functions->at(arguments.at(0));
}

// Все функции, кроме getFunctionOfDirectoryVector
StringFunction getStringUniversalFunction(const std::vector<std::string>& arguments) 
{
    auto functions = std::make_unique<std::map<std::string, StringFunction>>();
    *functions = {
        {"rename", [arguments]() {
            element::rename(arguments.at(1), arguments.at(2));
            return "\0";
        }},
        {"copy", [arguments]() {
            element::copy(arguments.at(1), arguments.at(2));
            return "\0";
        }},
        {"pwd", [arguments]() {
            return element::pwd(arguments.at(1));
        }},
        {"cat", [arguments]() {
            return filemaneger::file::readFile(arguments.at(1));
        }},
        {"echo", [arguments]() {
            file::writeFile(arguments.at(1), arguments.at(2));
            return "\0";
        }},
        {"touch", [arguments](){
            file::createFile(arguments.at(1));
            return "\0";
        }},
        {"rm", [arguments](){
            file::deleteFile(arguments.at(1));
            return "\0";
        }},
        {"mkdir", [arguments]() { 
            directory::createDirectory(arguments.at(1)); 
            return "\0";
        }},
        {"rmdir", [arguments]() { 
            directory::deleteDirectory(arguments.at(1)); 
            return "\0";
        }},
        {"cls", []() {
            #ifdef _WIN32
                std::system("cls");
            #else
                std::system("clear");
            #endif
            return "\0";
        }}
    };
    return functions->at(arguments.at(0));
}