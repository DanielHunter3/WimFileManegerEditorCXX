// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <filesystem>
#include <vector>
#include <string>

#include "header/filemaneger.hpp"

std::vector<std::string> getFilesInDirectory(const std::string& directoryPath) {
    std::vector<std::string> files;
    for (const auto& entry : std::filesystem::directory_iterator(directoryPath)) {
        if (entry.is_regular_file()) {
            files.emplace_back(entry.path().filename().string());
        }
    }
    return files;
}

std::vector<std::string> getDirectoriesInDirectory(const std::string& directoryPath) {
    std::vector<std::string> directories;
    for (const auto& entry : std::filesystem::directory_iterator(directoryPath)) {
        if (entry.is_directory()) {
            directories.emplace_back(entry.path().filename().string());
        }
    }
    return directories;
}

std::vector<std::string> getFilesAndDirectories(const std::string& directoryPath) {
    std::vector<std::string> files = getFilesInDirectory(directoryPath);
    std::vector<std::string> directories = getDirectoriesInDirectory(directoryPath);
    std::vector<std::string> result(std::move(directories));
    result.insert(result.end(), files.begin(), files.end());
    return result;
}

std::string getCurrentWorkingDirectory() {
    return std::filesystem::current_path().string();
}