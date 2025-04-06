#pragma once

#include <filesystem>
#include <string>
#include <array>
#include <map>
#include <optional>
#include <vector>

#include "uresult.hpp"

namespace fs = std::filesystem;
using fs::perms;

namespace filemaneger {}

namespace filemaneger::element { 
    struct DataPermission {
        std::string name;
        std::filesystem::perms perm = fs::perms::none;
        // add, remove, replace
        std::filesystem::perm_options option = std::filesystem::perm_options::replace;
    };
    struct PermissionMapping {
        char userType;
        char permission;
        fs::perms value;
    };
    struct OperationMapping {
        char op;
        fs::perm_options option;
    };

    fs::perms getPermissionValue(const char&, const char&) noexcept;
    UResult<DataPermission> getDataPerm(const std::string&, const std::string&) noexcept;
    bool isOnPermission(const std::filesystem::perms& perm, const std::string&) noexcept;
    UResult<std::map<std::filesystem::perms, bool>> getPermissions(const std::string&) noexcept;
    bool reperm(const DataPermission&) noexcept;
    std::string pwd(const std::string&) noexcept;
    bool exists(const std::string&) noexcept;
    bool rename(const std::string&, const std::string&) noexcept;
    void copy(const std::string&, const std::string&);
    bool remove(const std::string&) noexcept;
    bool create(const std::string&) noexcept;
}

namespace filemaneger::file {
    bool deleteFile(const std::string&) noexcept;
    bool createFile(const std::string&) noexcept;
    bool writeFile(const std::string& filename, 
                    const std::string& string, 
                    std::ios_base::openmode mode  = std::ios::out) noexcept;
    std::optional<std::string> readFile(const std::string&) noexcept;
}

namespace filemaneger::directory {
    bool createDirectory(const std::string&) noexcept;
    bool changeDirectory(const std::string&) noexcept;
    bool deleteDirectory(const std::string&) noexcept;

    std::vector<std::string> getFilesInDirectory(const std::string&) noexcept;
    std::vector<std::string> getDirectoriesInDirectory(const std::string&) noexcept;
    std::vector<std::string> getFilesAndDirectories(const std::string&) noexcept;
    std::string getCurrentWorkingDirectory(void) noexcept;
}