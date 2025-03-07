// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <fstream>
#include <sys/stat.h>

#if defined(__unix__)
    #include <unistd.h>
#endif

#include "details.hpp"

#include "element.hpp"

namespace fs = std::filesystem;

namespace filemaneger {}

namespace filemaneger::element {

    std::array<Permission, 9> getAllPermissions() noexcept {
        std::array<Permission, 9> allPerms = {
            OWNER_READ, OWNER_WRITE, OWNER_EXECUTE, 
            GROUP_READ, GROUP_WRITE, GROUP_EXECUTE, 
            OTHERS_READ, OTHERS_WRITE, OTHERS_EXECUTE
        };
        return allPerms;
    }

    bool isOnPermission(const Permission& perm, const std::string& name) noexcept {
        fs::perms p = fs::status(name).permissions();
        std::map<Permission, std::filesystem::perms> map = {
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
        return (p & map[perm]) != fs::perms::none;
    }

    std::map<Permission, bool> getPermissions(const std::string& name) noexcept {
        std::map<Permission, bool> map;
        for (const auto& permission : getAllPermissions()) {
            map[permission] = isOnPermission(permission, name);
        }
        return map;
    }

    //TODO
    void setPermissions(const std::string& name, const fs::perms& permissions) noexcept {
        fs::permissions(name, permissions);
    }

    //TODO
    void reperm(const std::string& name, const fs::perms& permission, bool isActive) noexcept {
        fs::perms p = fs::status(name).permissions();
        if (isActive) { p |= permission; } 
        else { p &= ~permission; }
    }

    std::string pwd(const std::string& name) noexcept {
        return fs::absolute(name).string();
    }

    bool exists(const std::string& name) noexcept {
        return fs::exists(name);
    }

    bool rename(const std::string& name, const std::string& newName) noexcept {
        try {
            fs::rename(name, newName);
        } catch (const std::exception& e) {
            return false;
        }
        return true;
    }

    void copy(const std::string& source, const std::string& destination) {
        fs::copy(source, destination);
    }

    bool remove(const std::string& name) noexcept {
        return fs::remove(name); 
    }

    bool create(const std::string& name) noexcept {
        if (fs::exists(name)) {
            return false;
        }
        if (in(name, '.')) { filemaneger::file::createFile(name); }
        else { filemaneger::directory::createDirectory(name); }
        return true;
    }
}

namespace filemaneger::file {

    bool deleteFile(const std::string& path) noexcept {
        if (!fs::remove(path)) {
            return false;
        }
        return true;
    }

    bool createFile(const std::string& path) noexcept{
        if (fs::exists(path)) {
            return false;
        }
        std::ofstream file(path);
        if (!file.is_open()) {
            return false;
        }
        file.close();
        return true;
    }

    bool writeFile(const std::string& filename, 
                    const std::string& string, 
                    std::ios_base::openmode mode) noexcept
    {
        std::ofstream file(filename, mode);
        if (!file.is_open()) {
            return false;
        }
        file << string;
        file.close();
        return true;
    }

    std::optional<std::string> readFile(const std::string& filename) noexcept {
        std::ifstream file(filename);
        std::string result, line;
        if (!file.is_open()) {
            return std::nullopt;
        }
        while (std::getline(file, line)) {
            result += line + "\n";
        }
        return std::make_optional<std::string>(result);
    }
}

namespace filemaneger::directory {

    bool createDirectory(const std::string& dirname) noexcept {
        int result = -1;

        #if defined(WIN32)
            result = mkdir(dirname.c_str());
        #elif defined(__unix__)
            result = mkdir(dirname.c_str(), 0777);
        #endif

        if (result == -1) {
            return false;
        }
        return true;
    }

    bool changeDirectory(const std::string& dirname) noexcept {
        if (chdir(dirname.c_str()) == -1) {
            return false;
        }
        return true;
    }

    bool deleteDirectory(const std::string& dirname) noexcept {
        if (rmdir(dirname.c_str()) == -1) {
            return false;
        }
        return true;
    }

    std::vector<std::string> getFilesInDirectory(const std::string& directoryPath) noexcept {
        std::vector<std::string> files;
        for (const auto& entry : std::filesystem::directory_iterator(directoryPath)) {
            if (entry.is_regular_file()) {
                files.emplace_back(entry.path().filename().string());
            }
        }
        return files;
    }

    std::vector<std::string> getDirectoriesInDirectory(const std::string& directoryPath) noexcept {
        std::vector<std::string> directories;
        for (const auto& entry : std::filesystem::directory_iterator(directoryPath)) {
            if (entry.is_directory()) {
                directories.emplace_back(entry.path().filename().string());
            }
        }
        return directories;
    }

    std::vector<std::string> getFilesAndDirectories(const std::string& directoryPath) noexcept {
        std::vector<std::string> files = getFilesInDirectory(directoryPath);
        std::vector<std::string> directories = getDirectoriesInDirectory(directoryPath);
        std::vector<std::string> result(std::move(directories));
        result.insert(result.end(), files.begin(), files.end());
        return result;
    }

    std::string getCurrentWorkingDirectory(void) noexcept {
        return std::filesystem::current_path().string();
    }
}