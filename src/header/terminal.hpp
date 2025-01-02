#pragma once

#include <vector>
#include <string>

std::vector<std::string> getCommand(std::string& command);

std::vector<std::string> setTerminal();

bool getTerminal(const std::vector<std::string>& tokens);

void terminal();