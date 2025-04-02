// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "element.hpp"
#include "communist.hpp"

#include "commandhandler.hpp"

UResult<Universal> CommandHandler(const Function& func, 
                                const std::vector<std::string>& arguments) noexcept 
{
    Universal result;
    switch (func) {
        // ----------------------------------------------------------------
        case Rename:
            if (arguments.size() < 3) {
                return StructError {EnumError::InvalidArgumentError};
            }
            if (!filemaneger::element::rename(arguments[1], arguments[2])) {
                return StructError {EnumError::ElementRenameError};
            }
            result = "\0";
            break;
        // ----------------------------------------------------------------
        case Copy:
            if (arguments.size() > 3) {
                return StructError {EnumError::InvalidArgumentError}; 
            }
            filemaneger::element::copy(arguments[1], arguments[2]);
            result = "\0";
            break;
        // ----------------------------------------------------------------
        case Pwd:
            if (arguments.size() > 2) {
                return StructError {EnumError::InvalidArgumentError};
            }  
            result = filemaneger::element::pwd(arguments[1]);
            break;
        // ----------------------------------------------------------------
        case Cat:
            if (arguments.size() < 2) {
                return StructError {EnumError::InvalidArgumentError};
            }
            if (auto target = filemaneger::file::readFile(arguments[1]); 
                            target != std::nullopt) {
                result = *target;
            }
            else {
                return StructError {EnumError::FileReadError, "Couldn't read the file"};
            }
            break;
        // ----------------------------------------------------------------
        case Echo:
            if (arguments.size() < 3) {
                return StructError {EnumError::InvalidArgumentError};
            }
            if (!filemaneger::file::writeFile(arguments[1], arguments[2], std::ios::out)) {
                return StructError {EnumError::FileWriteError, "Failed to write information to a file"};
            }
            result = "\0";
            break;
        // ----------------------------------------------------------------
        case Mkdir:
            if (arguments.size() < 2) {
                return StructError {EnumError::InvalidArgumentError};
            }
            if (!filemaneger::directory::createDirectory(arguments[1])) {
                return StructError {EnumError::ElementCreateError, "Couldn't create folder"};
            }
            result = "\0";
            break;
        // ----------------------------------------------------------------
        case Rmdir:
            if (arguments.size() < 2) {
                return StructError {EnumError::RangeOutError};
            }
            if (!filemaneger::directory::deleteDirectory(arguments[1])) {
                return StructError {EnumError::ElementDeleteError, "Couldn't delete folder"};
            }
            result = "\0";
            break;
        // ----------------------------------------------------------------
        case Touch:
            if (arguments.size() < 2) {
                return StructError {EnumError::InvalidArgumentError};
            }
            if (!filemaneger::file::createFile(arguments[1])) {
                return StructError {EnumError::ElementCreateError, "Failed to create a file"};
            }
            result = "\0";
            break;
        // ----------------------------------------------------------------
        case Rm:
            if (arguments.size() < 2) {
                return StructError {EnumError::InvalidArgumentError};
            }
            if (!filemaneger::file::deleteFile(arguments[1])) {
                return StructError {EnumError::ElementDeleteError, "Failed to delete a file"};
            }
            result = "\0";
            break;
        // ----------------------------------------------------------------
        case Ls:
            result = filemaneger::directory::getFilesAndDirectories(".");
            break;
        // ----------------------------------------------------------------
        case Cd:
            if (arguments.size() < 2) {
                return StructError {EnumError::InvalidArgumentError};
            }
            if (!filemaneger::directory::changeDirectory(arguments[1])) {
                return StructError {EnumError::ChangeDirectoryError};
            }
            result = "\0";
            break;
        // ----------------------------------------------------------------
        case Cut:
            if (arguments.size() < 3) {
                return StructError {EnumError::InvalidArgumentError};
            }
            filemaneger::element::copy(arguments[1], arguments[2]);
            if (!filemaneger::element::remove(arguments[1])) {
                return StructError {EnumError::ElementDeleteError};
            }
            result = "\0";
            break;
        // ----------------------------------------------------------------
        case Cls:
            #ifdef _WIN32
                std::system("cls");
            #else
                std::system("clear");
            #endif
            result = "\0";
            break;
        // ----------------------------------------------------------------
        // TODO: Perm and Reperm
        // ----------------------------------------------------------------
        default:
            return StructError {EnumError::UnknownElementError, "The command could not be recognized"};
            break;
    }
    return result;
}