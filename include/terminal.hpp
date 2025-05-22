#pragma once

#include <vector>
#include <string>

#include "uresult.hpp"

std::vector<std::string> getCommand(const std::string&);

std::vector<std::string> setTerminal();

UResult<bool> getTerminal(const std::vector<std::string>&) noexcept;

void terminal();