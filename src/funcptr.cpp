// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <map>
#include <cstdlib>
#include <memory>

#include "header/element.hpp"
#include "header/funcptr.hpp"

using namespace filemaneger;

StringFunction getElementFunction(const std::vector<std::string>& arguments) {
    auto filename = arguments.at(1);
    std::unique_ptr<std::map<std::string, StringFunction>> map(new std::map<std::string, StringFunction>);
    *map = {
        {"rename", [filename, arguments]() {
            element::rename(filename, arguments.at(2));
            return std::string{"Renamed"};
        }},
        {"copy", [filename, arguments]() {
            element::copy(filename, arguments.at(2));
            return std::string{"Copied"};
        }},
        {"pwd", [filename]() {
            return element::pwd(filename);
        }}
    };
    return map->at(arguments.at(0));
}

StringFunction getFunctionOfFile(const std::vector<std::string>& arguments) {
    const auto filename = arguments.at(1);
    std::unique_ptr<std::map<std::string, StringFunction>> map(new std::map<std::string, StringFunction>);
    *map = {
        {"cat", [filename]() {
            return filemaneger::file::readFile(filename);
        }},
        {"echo", [filename, arguments]() {
            file::writeFile(filename, arguments.at(2));
            return std::string{"Information in " + filename + " has been completed"};
        }},
        {"touch", [filename](){
            file::createFile(filename);
            return std::string{"File created: " + filename};
        }},
        {"rm", [filename](){
            file::deleteFile(filename);
            return std::string{"File deleted: " + filename};
        }}
    };
    return map->at(arguments.at(0));
}

VectorStringFunction getFunctionOfDirectoryVector(const std::vector<std::string>& arguments) 
{
    std::unique_ptr<std::map<std::string, VectorStringFunction>> functions(new std::map<std::string, VectorStringFunction>); 
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

StringFunction getFunctionOfDirectoryString(const std::vector<std::string>& arguments) 
{
    std::unique_ptr<std::map<std::string, StringFunction>> functions(new std::map<std::string, StringFunction>); 
    *functions = {
        {"mkdir", [arguments]() { 
            directory::createDirectory(arguments.at(1)); 
            return std::string{"Directory created: " + arguments.at(1)};
        }},
        {
            "rmdir", [arguments]() { directory::deleteDirectory(arguments.at(1)); 
            return std::string{"Directory deleted: " + arguments.at(1)};
        }},
        {"cls", []() {
            #ifdef _WIN32
                std::system("cls");
            #else
                std::system("clear");
            #endif
            return std::string{"\0"};
        }}
    };
    return functions->at(arguments.at(0));
}

StringFunction getStringUniversalFunction(const std::vector<std::string>& arguments) 
{
    std::unique_ptr<std::map<std::string, StringFunction>> functions(new std::map<std::string, StringFunction>);
    *functions = {
        {"rename", [arguments]() {
            element::rename(arguments.at(1), arguments.at(2));
            return std::string{"Renamed"};
        }},
        {"copy", [arguments]() {
            element::copy(arguments.at(1), arguments.at(2));
            return std::string{"Copied"};
        }},
        {"pwd", [arguments]() {
            return element::pwd(arguments.at(1));
        }},
        {"cat", [arguments]() {
            return filemaneger::file::readFile(arguments.at(1));
        }},
        {"echo", [arguments]() {
            file::writeFile(arguments.at(1), arguments.at(2));
            return std::string{"Information in " + arguments.at(1) + " has been completed"};
        }},
        {"touch", [arguments](){
            file::createFile(arguments.at(1));
            return std::string{"File created: " + arguments.at(1)};
        }},
        {"rm", [arguments](){
            file::deleteFile(arguments.at(1));
            return std::string{"File deleted: " + arguments.at(1)};
        }},
        {"mkdir", [arguments]() { 
            directory::createDirectory(arguments.at(1)); 
            return std::string{"Directory created: " + arguments.at(1)};
        }},
        {"rmdir", [arguments]() { 
            directory::deleteDirectory(arguments.at(1)); 
            return std::string{"Directory deleted: " + arguments.at(1)};
        }},
        {"cls", []() {
            #ifdef _WIN32
                std::system("cls");
            #else
                std::system("clear");
            #endif
            return std::string{"\0"};
        }}
    };
    return functions->at(arguments.at(0));
}