#pragma once

#include <filesystem>
#include <string>
#include <array>
#include <map>

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

    std::array<Permission, 9> getAllPermissions();
    bool isOnPermission(const Permission& perm, const std::string& name);
    std::map<Permission, bool> getPermissions(const std::string& name);
    void setPermissions(const std::string& name, const std::filesystem::perms& permissions);
    void reperm(const std::string& name, const std::filesystem::perms& permission, bool isActive);
    std::string pwd(const std::string& name);
    bool exists(const std::string& name);
    void rename(const std::string& name, const std::string& newName);
    void copy(const std::string& source, const std::string& destination);
    void remove(const std::string& name);
    void create(const std::string& name);
}

namespace filemaneger::file {
    void deleteFile(const std::string& path);
    void createFile(const std::string& path);
    void writeFile(const std::string& filename, 
                    const std::string& string, 
                    std::ios_base::openmode mode  = std::ios::out);
    std::string readFile(const std::string& filename);
}

namespace filemaneger::directory {
    void createDirectory(const std::string& dirname);
    void changeDirectory(const std::string& dirname);
    void deleteDirectory(const std::string& dirname);
}