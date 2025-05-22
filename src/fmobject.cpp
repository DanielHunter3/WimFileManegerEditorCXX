// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <map>
#include <memory>
#include <stdexcept>

#include "fmobject.hpp"

using enum Type;

FMObject::FMObject(const Universal& command)
  : m_command(command)
{
  if (std::holds_alternative<std::string>(command)) m_type = STR;
  else if (std::holds_alternative<std::vector<std::string>>(command)) m_type = VECSTR;
  else if (std::holds_alternative<std::nullopt_t>(command)) m_type = NONE;
  else throw std::runtime_error("Unknown type");
}
FMObject::~FMObject() = default;

Type FMObject::setType() const noexcept { return m_type; }
std::string FMObject::toTerminal() const noexcept {
  if (m_type == NONE) { return "\0"; }
  if (m_type == VECSTR) {
    const auto result = std::make_unique<std::string>();
    for (const auto& arg : std::get<std::vector<std::string>>(m_command)) {
      *result += arg + "\n";
    }
    return result->substr(0, result->size() - 1);
  }
  return std::get<std::string>(m_command);
}

std::string typeToString(const Type& type) noexcept { 
  std::map<Type, std::string> map = {
    {STR, "STR"},
    {VECSTR, "VECSTR"},
    {NONE, "NONE"},
  };
  return map[type];
}