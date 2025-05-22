// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "commandhandler.hpp"
#include "utildef.hpp"

#include "usercommand.hpp"

UResult<FMObject> getFMObject(const std::vector<std::string>& args) noexcept {
  if (args.empty()) return ResultError(EnumError::EmptyCommandError, "Empty Command");
  auto command = stringToFunction(args[0]);
  if (!command.has_value()) {
    return ResultErrorFrom(command.error());
  }
  auto object = CommandHandler(*command, args);
  if (!object.has_value()) {
    return ResultErrorFrom(object.error());
  }
  return FMObject(*object);
}
