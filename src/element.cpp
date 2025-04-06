// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <fstream>

#include "details.hpp"

#include "element.hpp"

namespace filemaneger {}

namespace filemaneger::element {
    constexpr std::array<fs::perms, 16> PERMS = {
        perms::owner_read, perms::owner_write, perms::owner_exec, perms::owner_all,
        perms::group_read, perms::group_write, perms::group_exec, perms::group_all,
        perms::others_read, perms::others_write, perms::others_exec, perms::others_all,
        //-------------------------------------------------------------------------
        perms::owner_read | perms::group_read | perms::others_read,
        perms::owner_write | perms::group_write | perms::others_write,
        perms::owner_exec | perms::group_exec | perms::others_exec,
        //--------------------------------------------------------------------------
        perms::all,
    };

    constexpr std::array<PermissionMapping, 16> permissionMappings {{
        {'u', 'r', perms::owner_read},
        {'u', 'w', perms::owner_write},
        {'u', 'x', perms::owner_exec},
        {'u', 'a', perms::owner_all},
    
        {'g', 'r', perms::group_read},
        {'g', 'w', perms::group_write},
        {'g', 'x', perms::group_exec},
        {'g', 'a', perms::group_all},
    
        {'o', 'r', perms::others_read},
        {'o', 'w', perms::others_write},
        {'o', 'x', perms::others_exec},
        {'o', 'a', perms::others_all},
    
        {'a', 'r', perms::owner_read | perms::group_read | perms::others_read},
        {'a', 'w', perms::owner_write | perms::group_write | perms::others_write},
        {'a', 'x', perms::owner_exec | perms::group_exec | perms::others_exec},
        {'a', 'a', perms::all}
    }};

    constexpr std::array<OperationMapping, 3> OPERATION_MAPPINGS {{
        {'+', fs::perm_options::add},
        {'-', fs::perm_options::remove},
        {'/', fs::perm_options::replace}
    }};

    fs::perms getPermissionValue(const char& userType, const char& permission) noexcept {
        static constexpr auto findPermission = [](const char& ut, const char& p) constexpr noexcept -> fs::perms {
            for (const auto& mapping : permissionMappings) {
                if (mapping.userType == ut && mapping.permission == p) {
                    return mapping.value;
                }
            }
            return perms::none;
        };
        return findPermission(userType, permission);
    }

    UResult<DataPermission> 
    getDataPerm(const std::string& name, const std::string& str) noexcept
    {
        if (str.length() != 3) {  // Минимальная длина: "u+r"
            return StructError {EnumError::InvalidArgumentError};
        }
    
        char operationChar = str[1];
        auto opIt = std::find_if(OPERATION_MAPPINGS.begin(), OPERATION_MAPPINGS.end(),
        [operationChar](const auto& mapping) { 
            return mapping.op == operationChar; 
        });

        if (opIt == OPERATION_MAPPINGS.end()) {
            return StructError {EnumError::UnknownElementError};
        }
    
        fs::perms perm = getPermissionValue(str[0], str[2]);
        if (perm == perms::none) {
            return StructError {EnumError::InvalidArgumentError};
        }
    
        return DataPermission {name, perm, opIt->option};
    }

    bool isOnPermission(const fs::perms& perm, const std::string& name) noexcept {
        // fs::perms p = fs::status(name).permissions();
        // return (p & perm) != fs::perms::none;
        if (!fs::exists(name)) {
            return false;
        }
        fs::perms currentPermissions = fs::status(name).permissions();
        // Проверяем, что все запрашиваемые биты разрешений установлены
        return (currentPermissions & perm) == perm;
    }

    UResult<std::map<fs::perms, bool>> getPermissions(const std::string& name) noexcept {
        if (!fs::exists(name)) {
            return StructError {EnumError::DataFoundError};
        }
        std::map<fs::perms, bool> map;
        
        // Получаем текущие разрешения файла один раз
        fs::perms currentPermissions = fs::status(name).permissions();
        
        for (const auto& permission : PERMS) {
            // Проверяем каждое разрешение
            map[permission] = (currentPermissions & permission) == permission;
        }
        return map;
    }

    bool reperm(const DataPermission& data) noexcept {
        if (!fs::exists(data.name)) {
            return false;
        }
        try {
            fs::permissions(
                data.name,
                data.perm,
                data.option
            );
        } catch (fs::filesystem_error& e) {
            return false;
        }
        return true;
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
        in(name, '.') ? 
            filemaneger::file::createFile(name) : filemaneger::directory::createDirectory(name);
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

    bool createFile(const std::string& path) noexcept {
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
        file.close();
        return std::make_optional<std::string>(result);
    }
}

namespace filemaneger::directory {

    bool createDirectory(const std::string& dirname) noexcept {
        return fs::create_directories(dirname);
    }

    bool changeDirectory(const std::string& dirname) noexcept {
        if (!fs::exists(dirname)) {
            return false;
        }
        fs::current_path(dirname);
        return true;
    }

    bool deleteDirectory(const std::string& dirname) noexcept {
        return (fs::remove_all(dirname) == -(1ULL) ? false : true);
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