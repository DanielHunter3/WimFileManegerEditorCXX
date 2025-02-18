#pragma once

#include <filesystem>
#include <string>
#include <array>
#include <map>
#include <optional>
#include <vector>

namespace filemaneger {}

namespace filemaneger::element {
    enum Permission {
        OWNER_READ,
        OWNER_WRITE,
        OWNER_EXECUTE,
        GROUP_READ,
        GROUP_WRITE,
        GROUP_EXECUTE,
        OTHERS_READ,
        OTHERS_WRITE,
        OTHERS_EXECUTE
    };

    std::array<Permission, 9> getAllPermissions() noexcept;
    bool isOnPermission(const Permission& perm, const std::string&) noexcept;
    std::map<Permission, bool> getPermissions(const std::string&) noexcept;
    void setPermissions(const std::string&, const std::filesystem::perms&) noexcept;
    void reperm(const std::string&, const std::filesystem::perms&, bool) noexcept;
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