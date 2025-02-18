// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "header/usercommand.hpp"
#include "header/details.hpp"
#include "header/commandhandler.hpp"

Result<FMObject> getFMObject(const std::vector<std::string>& args) noexcept {
    if (args.empty()) return ResultError {EmptyCommandError};
    auto command = stringToFunction(args[0]);
    if (command.is_error()) {
        return ResultError {command.error()};
    }
    auto object = CommandHandler(*command, args);
    if (object.is_error()) {
        return ResultError {object.error()};
    }
    FMObject fmobject(*object);
    return fmobject;
}
