#pragma once

#include <vector>
#include <string>

#include "resulthandler.hpp"

std::vector<std::string> getCommand(std::string&);

std::vector<std::string> setTerminal();

Result<bool> getTerminal(const std::vector<std::string>&) noexcept;

void terminal();