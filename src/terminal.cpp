// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <iostream>
#include <sstream>

#include "usercommand.hpp"
#include "terminal.hpp"
#include "element.hpp"
#include "utildef.hpp"

std::vector<std::string> getCommand(const std::string& command) {
  std::vector<std::string> tokens;
  std::string token;
  std::istringstream tokenStream(command);
  while (std::getline(tokenStream, token, ' ')) {
    tokens.push_back(token);
  }
  return tokens;
}

std::vector<std::string> setTerminal() {
  std::string command;
  std::cout << filemanager::directory::getCurrentWorkingDirectory() << "> ";
  std::getline(std::cin, command);
  return getCommand(command);
}

// TODO
// Оптимизировать: FMObject создается много раз в terminal(), надо переместить while в эту функцию
//-------------------------------
UResult<bool> getTerminal(const std::vector<std::string>& tokens) noexcept {
  if (tokens.empty()) {
    return ResultError(EnumError::EmptyCommandError, "No command specified!");
  }
  auto t = getFMObject(tokens);
  if (!t.has_value()) {
    if (t.error().type() == EnumError::ExitCommandError) return false;
    return ResultErrorFrom(t.error());
  }
  std::cout << t->toTerminal() << '\n';
  return true;
}

void terminal() {
  while (true)
  {
    auto t = getTerminal(setTerminal());
    if (!t.has_value()) {
      std::cerr << "Error: " << t.error().message() << '\n';
      continue;
    }
    if (!*t) {
      break;
    }
  }
}
//-----------------------------------