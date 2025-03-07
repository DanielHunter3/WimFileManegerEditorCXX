#pragma once

#include <variant>
#include <vector>
#include <string>

#include "resulthandler.hpp"
#include "communist.hpp"

using Universal = std::variant<std::vector<std::string>, std::string>;

Result<Universal> CommandHandler(const Function& func, 
                                const std::vector<std::string>& arguments) noexcept;