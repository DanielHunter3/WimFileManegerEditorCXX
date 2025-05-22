// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <fstream>

#include "details.hpp"
#include "utildef.hpp"

#include "element.hpp"

namespace filemanager {}

namespace filemanager::element {
  UResult<std::string> pwd(const std::string& name) noexcept {
    std::filesystem::__cxx11::path result;
    try {
      result = fs::absolute(name);
    } catch (fs::filesystem_error& e) {
      return ResultFSError("pwd", name, e);
    }
    return result.string();
  }

  VOption rename(const std::string& name, const std::string& newName) noexcept {
    if (!fs::exists(name)) {
      return OptionNotFoundError("rename", name);
    }
    try {
      fs::rename(name, newName);
    } catch (const std::exception& e) {
      return OptionFSError("rename", name, e);
    }
    return VOID;
  }

  VOption remove(const std::string& el) noexcept {
    IfOptionByOptionError(in(el, '.') ? file::createFile(el) : directory::deleteDirectory(el));
    return VOID;
  }

  VOption copy(const std::string& source, const std::string& destination) noexcept {
    try {
      fs::copy(source, destination);
    } catch (fs::filesystem_error& e) {
      return OptionFSError("cp", "...", e);
    }
    return VOID;
  }

  VOption cut(const std::string& source, const std::string& dest) noexcept {
    IfOptionByOptionError(element::copy(source, dest));
    IfOptionByOptionError(element::remove(source));
    return VOID;
  }
}

namespace filemanager::element::permission {
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

  perms getPermissionValue(const char& userType, const char& permission) noexcept {
    static constexpr auto findPermission = 
      [](const char& ut, const char& p) constexpr noexcept -> perms
      {
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
    if (str.length() != 3) { // std::string("u+r").size() == 3
      return ResultError(
        EnumError::InvalidArgumentError, 
        "Very long argument"
      );
    }
  
    char operationChar = str[1];
    auto opIt = std::find_if(OPERATION_MAPPINGS.begin(), OPERATION_MAPPINGS.end(),
    [operationChar](const auto& mapping) { 
      return mapping.op == operationChar; 
    });

    if (opIt == OPERATION_MAPPINGS.end()) {
      return ResultError(
        EnumError::ChmodError,
        "Operation has not been found"
      );
    }
  
    perms perm = getPermissionValue(str[0], str[2]);
    if (perm == perms::none) {
      return ResultError(
        EnumError::InvalidArgumentError,
        "AAA"
      );
    }
  
    return DataPermission {name, perm, opIt->option};
  }

  UResult<bool> isOnPermission(const perms& perm, const std::string& name) noexcept {
    if (!fs::exists(name)) {
      return ResultNotFoundError("chmod", name);
    }
    perms currentPermissions = fs::status(name).permissions();
    // Проверяем, что все запрашиваемые биты разрешений установлены
    return (currentPermissions & perm) == perm;
  }

  UResult<std::map<fs::perms, bool>> getPermissions(const std::string& name) noexcept {
    if (!fs::exists(name)) {
      return ResultNotFoundError("getchmod", name);
    }
    std::map<perms, bool> map;
    
    try {
      perms currentPermissions = fs::status(name).permissions();
    
      for (const auto& permission : PERMS) {
      // Проверяем каждое разрешение
        map[permission] = (currentPermissions & permission) == permission;
      }
    } catch (fs::filesystem_error& e) {
      return ResultFSError("getchmod", name, e);
    }
    return map;
  }

  VOption reperm(const DataPermission& data) noexcept {
    if (!fs::exists(data.name)) {
      return OptionNotFoundError("reperm", data.name);
    }
    try {
      fs::permissions(
        data.name,
        data.perm,
        data.option
      );
    } catch (fs::filesystem_error& e) {
      return OptionFSError("chmod", data.name, e);
    }
    return VOID;
  }
}

namespace filemanager::element::cli {
  void clearTerminal() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
  }
}

namespace filemanager::file {
  VOption deleteFile(const std::string& path) noexcept {
    if (!fs::exists(path)) {
      return OptionNotFoundError("rm", path);
    }
    if (!fs::remove(path)) {
      return OptionError(
        EnumError::ElementDeleteError, "AAA"
      );
    }
    return VOID;
  }

  VOption createFile(const std::string& path) noexcept {
    if (fs::exists(path)) {
      return OptionNotFoundError("touch", path);
    }
    std::ofstream file(path);
    if (!file.is_open()) {
      return OptionError(
        EnumError::ElementCreateError, "AAA"
      );
    }
    file.close();
    return VOID;
  }

  VOption writeFile(const std::string& filename,
          const std::string& string, 
          std::ios_base::openmode mode) noexcept
  {
    if (!fs::exists(filename)) {
      return OptionNotFoundError("echo", filename);
    }
    std::ofstream file(filename, mode);
    if (!file.is_open()) {
      return OptionError(
        EnumError::FileWriteError, "..."
      );
    }
    file << string;
    file.close();
    return VOID;
  }

  UResult<std::string> readFile(const std::string& filename) noexcept {
    if (!fs::exists(filename)) {
      return ResultNotFoundError("cat", filename);
    }
    std::ifstream file(filename);
    std::string result, line;
    if (!file.is_open()) {
      return ResultError(
        EnumError::FileReadError, ""
      );
    }
    while (std::getline(file, line)) {
      result += line + "\n";
    }
    file.close();
    return result;
  }
}

namespace filemanager::directory {
  VOption createDirectory(const std::string& dirname) noexcept {
    if (fs::exists(dirname)) {
      return OptionNotFoundError("mkdir", dirname);
    }
    if (!fs::create_directory(dirname)) { return OptionError(EnumError::ElementCreateError, "..."); };
    return VOID;
  }

  VOption changeDirectory(const std::string& dirname) noexcept {
    if (!fs::exists(dirname)) {
      return OptionNotFoundError("cd", dirname);
    }
    try {
      fs::current_path(dirname);
    } catch (fs::filesystem_error& e) {
      return OptionFSError("cd", dirname, e);
    }
    return VOID;
  }

  VOption deleteDirectory(const std::string& dirname) noexcept {
    if (!fs::exists(dirname)) {
      return OptionNotFoundError("rmdir", dirname);
    }
    if (!fs::remove(dirname)) {return OptionError(EnumError::ElementDeleteError, "..."); }
    return VOID;
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

  std::string getCurrentWorkingDirectory() noexcept {
    return std::filesystem::current_path().string();
  }
}