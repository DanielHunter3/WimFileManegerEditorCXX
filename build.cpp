// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <filesystem>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdexcept>

namespace fs = std::filesystem;

std::string compiler(std::string& dir, std::string& exe) {
    std::string result;
    #ifdef __GNUC__
        result = "g++ -o " + dir + "/" + exe + " ";
    #elif _MSC_VER
        throw std::logic_error("This compiler doesn't support");
    #elif __clang__
        result = "clang++ -o " + dir + "/" + exe + " ";
    #else
        throw std::runtime_error("Undefined compiler version");
    #endif
    return result;
}

std::vector<std::string> get_cpp_files(const std::string& directoryPath) {
    if (!fs::exists(directoryPath) || !fs::is_directory(directoryPath)) {
        throw std::runtime_error("Invalid directory path");
    }
    std::string dir = ((directoryPath == ".") ? "" : (directoryPath + "/"));
    std::vector<std::string> files;

    for (const auto& entry : fs::directory_iterator(directoryPath)) {
        std::string filename = entry.path().filename().string();
        if (filename != "build.cpp" && 
            (filename.find(".cpp") != std::string::npos && std::count(filename.begin(), filename.end(), '.') == 1) &&
            entry.is_regular_file()) {
            files.push_back(dir + filename);
        }
    }

    if (files.empty()) {
        throw std::runtime_error(".cpp file not found");
    }

    return files;
}

void build(std::string&& src, std::string&& dest, std::string&& exe) {
    std::string command = compiler(dest, exe);
    for (const auto& filename : get_cpp_files(src)) {
        command += filename + " ";
    }
    
    // Удаляем последний пробел
    command.pop_back();

    std::cout << "Building with command: " << command << "\n\n\n\n\n\n";

    // Выполняем команду и проверяем результат
    int result = system(command.c_str());
    if (result != 0) {
        throw std::runtime_error("Build failed with error code: " + std::to_string(result));
    }
}

int main() {
    std::cout << "--------------------------------\n" << "Building...\n" << "--------------------------------\n";
    try {
        build("src", "app", "app");
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << "--------------------------------\n" << "DONE\n" << "--------------------------------\n";
    
    return EXIT_SUCCESS;
}