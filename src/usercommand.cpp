// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "commandhandler.hpp"

#include "usercommand.hpp"

 UResult<FMObject> getFMObject(const std::vector<std::string>& args) noexcept {
    if (args.empty()) return StructError {EnumError::EmptyCommandError};
    auto command = stringToFunction(args[0]);
    if (command.is_error()) {
        return command.error();
    }
    auto object = CommandHandler(*command, args);
    if (object.is_error()) {
        return object.error();
    }
    //FMObject fmobject(*object);
    //return fmobject;
    return FMObject(*object);
}
