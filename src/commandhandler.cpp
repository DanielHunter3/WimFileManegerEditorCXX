// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "element.hpp"
#include "communist.hpp"
#include "utildef.hpp"

#include "commandhandler.hpp"

using enum Function;

UResult<Universal>
CommandHandler(const Function& func, const std::vector<std::string>& arguments) noexcept
{
  if (!validQuantityOfArguments(func, static_cast<int8_t>(arguments.size() - 1))) {
    return ResultError(EnumError::InvalidArgumentError, "...");
  }

  Universal result;
  switch (func) {
    // ----------------------------------------------------------------
    case Rename:
      IfOptionByResultError(filemanager::element::rename(arguments[1], arguments[2]));
      return std::nullopt;
    // ----------------------------------------------------------------
    case Copy:
      IfOptionByResultError(filemanager::element::copy(arguments[1], arguments[2]));
      return std::nullopt;
    // ----------------------------------------------------------------
    case Pwd:
      if (auto value = filemanager::element::pwd(arguments[1]); !value.has_value()) {
        ResultErrorFrom(value.error());
      } else {
        result = *value;
      }
      break;
    // ----------------------------------------------------------------
    case Cat:
      if (auto target = filemanager::file::readFile(arguments[1]); target.has_value()) {
        result = *target;
      } else {
        return ResultErrorFrom(target.error());
      }
      break;
    // ----------------------------------------------------------------
    case Echo:
      IfOptionByResultError(filemanager::file::writeFile(arguments[1], arguments[2], std::ios::out));
      return std::nullopt;
    // ----------------------------------------------------------------
    case Mkdir:
      IfOptionByResultError(filemanager::directory::createDirectory(arguments[1]));
      return std::nullopt;
    // ----------------------------------------------------------------
    case Rmdir:
      IfOptionByResultError(filemanager::directory::deleteDirectory(arguments[1]));
      return std::nullopt;
    // ----------------------------------------------------------------
    case Touch:
      IfOptionByResultError(filemanager::file::createFile(arguments[1]));
      return std::nullopt;
    // ----------------------------------------------------------------
    case Rm:
      IfOptionByResultError(filemanager::file::deleteFile(arguments[1]));
      return std::nullopt;
    // ----------------------------------------------------------------
    case Ls:
      result = filemanager::directory::getFilesAndDirectories(".");
      break;
    // ----------------------------------------------------------------
    case Cd:
      IfOptionByResultError(filemanager::directory::changeDirectory(arguments[1]));
      return std::nullopt;
    // ----------------------------------------------------------------
    case Cut:
      IfOptionByResultError(filemanager::element::cut(arguments[1], arguments[2]));
      return std::nullopt;
    // ----------------------------------------------------------------
    case Cls:
      filemanager::element::cli::clearTerminal();
      return std::nullopt;
    // ----------------------------------------------------------------
    case Chmod: {
      const auto arg = filemanager::element::permission::getDataPerm(arguments[1], arguments[2]);
      if (!arg.has_value()) {
        return ResultErrorFrom(arg.error());
      }
      IfOptionByResultError(filemanager::element::permission::reperm(*arg));
      return std::nullopt;
    }
    // ----------------------------------------------------------------
    case Exit:
      return ResultError(EnumError::ExitCommandError, "Exit to command");
    //----------------------------------------------------------------
    default:
      return ResultError(EnumError::UnknownError, "The command could not be recognized");
  }
  return result;
}