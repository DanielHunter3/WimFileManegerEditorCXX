#pragma once

#include <vector>
#include <string>

std::vector<std::string> getFilesInDirectory(const std::string& directoryPath);

std::vector<std::string> getDirectoriesInDirectory(const std::string& directoryPath);

std::vector<std::string> getFilesAndDirectories(const std::string& directoryPath);

std::string getCurrentWorkingDirectory();