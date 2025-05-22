/*
include/element.hpp
Here are the main functions for working with the file system.

Namespaces:
1. filemanager::element:
  a. Functions for working with folders and files.
  b. The permission namespace for working with permissions.
2. filemanager::file. For working with files.
3. filemanager::directory. For working with folders.

Functions are divided into 3 types by the return value:
1. "Bare" value. The function cannot return errors => does not require validation;
2. std::optional<T>. Most often, the T type is BOOL. 
  The function returns std::nullopt if the file system element was not found, 
  FALSE if the fs::filesystem_error exception was thrown and caught, 
  TRUE if everything went well;
3. Result<T>. 
  Returns type T if everything went well, Strict Error<E num Error>> if some error occurred. 
  The first returned element (error() method) is an enumeration 
  (usually either that the file system element was not found, or the fs::filesystem_error exception was caught), 
  the second (message() method) is the error message.
*/

#pragma once

#include <filesystem>
#include <string>
#include <map>
#include <optional>
#include <vector>

#include "uresult.hpp"

namespace fs = std::filesystem;
using fs::perms;

namespace filemanager {}

namespace filemanager::element {
  UResult<std::string> pwd(const std::string&) noexcept;
  VOption rename(const std::string&, const std::string&) noexcept;
  VOption copy(const std::string&, const std::string&) noexcept;
  VOption cut(const std::string&, const std::string&) noexcept;
  VOption remove(const std::string&) noexcept;
  VOption create(const std::string&) noexcept; // TODO or Delete
}

namespace filemanager::element::permission {
  struct DataPermission {
    std::string name;
    perms perm = perms::none;
    // add, remove, replace
    fs::perm_options option = fs::perm_options::replace;
  };
  struct PermissionMapping {
    char userType;
    char permission;
    perms value;
  };
  struct OperationMapping {
    char op;
    fs::perm_options option;
  };

  perms getPermissionValue(const char&, const char&) noexcept;
  UResult<DataPermission> getDataPerm(const std::string&, const std::string&) noexcept;
  UResult<bool> isOnPermission(const perms& perm, const std::string&) noexcept;
  UResult<std::map<perms, bool>> getPermissions(const std::string&) noexcept;
  VOption reperm(const DataPermission&) noexcept;
}

namespace filemanager::element::cli {
    void clearTerminal();
}

namespace filemanager::file {
  VOption deleteFile(const std::string&) noexcept;
  VOption createFile(const std::string&) noexcept;
  VOption writeFile(const std::string& filename,
          const std::string& string, 
          std::ios_base::openmode mode = std::ios::out) noexcept;
  UResult<std::string> readFile(const std::string&) noexcept;
}

namespace filemanager::directory {
  VOption createDirectory(const std::string&) noexcept;
  VOption changeDirectory(const std::string&) noexcept;
  VOption deleteDirectory(const std::string&) noexcept;

  std::vector<std::string> getFilesInDirectory(const std::string&) noexcept;
  std::vector<std::string> getDirectoriesInDirectory(const std::string&) noexcept;
  std::vector<std::string> getFilesAndDirectories(const std::string&) noexcept;
  std::string getCurrentWorkingDirectory() noexcept;
}