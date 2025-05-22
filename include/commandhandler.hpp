#pragma once

#include <variant>
#include <vector>
#include <string>

#include "uresult.hpp"
#include "communist.hpp"

using Universal = std::variant<std::vector<std::string>, std::string, std::nullopt_t>;

UResult<Universal> CommandHandler(const Function& func,
                const std::vector<std::string>& arguments) noexcept;