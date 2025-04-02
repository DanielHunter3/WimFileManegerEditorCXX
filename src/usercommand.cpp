// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "usercommand.hpp"
#include "details.hpp"
#include "commandhandler.hpp"

 UResult<FMObject> getFMObject(const std::vector<std::string>& args) noexcept {
    if (args.empty()) return StructError {EnumError::EmptyCommandError};
    auto command = stringToFunction(args[0]);
    if (command.is_error()) {
        return StructError {command.error()};
    }
    auto object = CommandHandler(*command, args);
    if (object.is_error()) {
        return StructError {object.error()};
    }
    FMObject fmobject(*object);
    return fmobject;
}
