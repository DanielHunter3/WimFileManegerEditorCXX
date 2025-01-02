// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <string>
#include <memory>
#include <filesystem>
#include <array>
#include <map>
#include <sys/stat.h>
#include <fstream>

#include "header/details.hpp"
#include "header/customexception.hpp"

#include "header/element.hpp"

namespace fs = std::filesystem;

namespace filemaneger {}

namespace filemaneger::element {

    // enum Permission {
    //     OWNER_READ,
    //     OWNER_WRITE,
    //     OWNER_EXECUTE,
    //     GROUP_READ,
    //     GROUP_WRITE,
    //     GROUP_EXECUTE,
    //     OTHERS_READ,
    //     OTHERS_WRITE,
    //     OTHERS_EXECUTE
    // };

    std::array<Permission, 9> getAllPermissions() {
        auto allPerms = std::make_unique<std::array<Permission, 9>>();
        *allPerms = {
            OWNER_READ, OWNER_WRITE, OWNER_EXECUTE, 
            GROUP_READ, GROUP_WRITE, GROUP_EXECUTE, 
            OTHERS_READ, OTHERS_WRITE, OTHERS_EXECUTE
        };
        return *allPerms;
    }

    bool isOnPermission(const Permission& perm, const std::string& name) {
        fs::perms p = fs::status(name).permissions();
        auto map = std::make_unique<std::map<Permission, std::filesystem::perms>>();
        *map = {
            {OWNER_READ, std::filesystem::perms::owner_read},
            {OWNER_WRITE, std::filesystem::perms::owner_write},
            {OWNER_EXECUTE, std::filesystem::perms::owner_exec},
            {GROUP_READ, std::filesystem::perms::group_read},
            {GROUP_WRITE, std::filesystem::perms::group_write},
            {GROUP_EXECUTE, std::filesystem::perms::group_exec},
            {OTHERS_READ, std::filesystem::perms::others_read},
            {OTHERS_WRITE, std::filesystem::perms::others_write},
            {OTHERS_EXECUTE, std::filesystem::perms::others_exec}
        };
        return (p & map->at(perm)) != fs::perms::none;
    }

    std::map<Permission, bool> getPermissions(const std::string& name) {
        auto map = std::make_unique<std::map<Permission, bool>>();
        for (const auto& permission : getAllPermissions()) {
            (*map)[permission] = isOnPermission(permission, name);
        }
        return *map;
    }

    void setPermissions(const std::string& name, const fs::perms& permissions) {
        fs::permissions(name, permissions);
    }

    void reperm(const std::string& name, const fs::perms& permission, bool isActive) {
        fs::perms p = fs::status(name).permissions();
        if (isActive) { p |= permission; } 
        else { p &= ~permission; }
    }

    std::string pwd(const std::string& name) {
        return fs::absolute(name).string();
    }

    bool exists(const std::string& name) {
        return fs::exists(name);
    }

    void rename(const std::string& name, const std::string& newName) {
        fs::rename(name, newName);
    }

    void copy(const std::string& source, const std::string& destination) {
        fs::copy(source, destination);
    }

    void remove(const std::string& name) {
        if (!fs::remove(name)) {
            throw ElementDeleteException("Error of delete element");
        }
    }

    void create(const std::string& name) {
        if (fs::exists(name)) {
            throw ElementCreateException(("File or directory already exists: " + name).c_str());
        }
        if (in(name, '.')) { filemaneger::file::createFile(name); }//
        else { filemaneger::directory::createDirectory(name); }
    }
}

namespace filemaneger::file {

    void deleteFile(const std::string& path) {
        if (!fs::remove(path)) {
            throw ElementDeleteException(("Error deleting file: " + path).c_str());
        }
    }

    void createFile(const std::string& path) {
        if (fs::exists(path)) {
            throw ElementCreateException(("File have already created: " + path).c_str());
        }
        auto file = std::make_unique<std::ofstream>(path);
        if (!file->is_open()) {
            throw ElementCreateException(("Error opening file: " + path).c_str());
        }
        file->close();
    }

    void writeFile(const std::string& filename, 
                    const std::string& string, 
                    std::ios_base::openmode mode) 
    {
        std::ofstream file(filename, mode);
        if (!file.is_open()) {
            throw FileWriteException(("Error opening file: " + filename).c_str());
        }
        file << string;
        file.close();
    }

    std::string readFile(const std::string& filename) {
        std::ifstream file(filename);
        std::string result, line;
        if (!file.is_open()) {
            throw FileReadException(("Error opening file: " + filename).c_str());
        }
        while (std::getline(file, line)) {
            result += line + "\n";
        }
        return result;
    }
}

namespace filemaneger::directory {

    void createDirectory(const std::string& dirname) {
        if (mkdir(dirname.c_str()) == -1) {
            throw ElementCreateException(("Could not create directory: " + dirname).c_str());
        }
    }

    void changeDirectory(const std::string& dirname) {
        if (chdir(dirname.c_str()) == -1) {
            throw ChangeDirectoryException(("Could not change directory to: " + dirname).c_str());
        }
    }

    void deleteDirectory(const std::string& dirname) {
        if (rmdir(dirname.c_str()) == -1) {
            throw ElementDeleteException(("Could not delete directory: " + dirname).c_str());
        }
    }

}