#pragma once

#include <vector>
#include <string>
#include <variant>

#include "commandhandler.hpp"

enum class Type {
  STR, VECSTR, NONE,
};

class FMObject {
public:
  explicit FMObject(const Universal& command);
  FMObject() = delete;
  ~FMObject();

  Type setType() const noexcept;
  std::string toTerminal() const noexcept;

private:
  Universal m_command;
  Type m_type;
};

std::string typeToString(const Type& type) noexcept;