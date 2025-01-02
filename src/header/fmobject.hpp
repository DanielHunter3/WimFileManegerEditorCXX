#pragma once

#include <vector>
#include <string>
#include <variant>

using command_t = std::variant<std::vector<std::string>, std::string>;

enum Type {
    STR, VECSTR, UNKNOWN
};

class FMCommand {
public:
    FMCommand(const std::vector<std::string>& command);
    FMCommand(const std::string& command);
    ~FMCommand();

    Type setType() const noexcept;
    std::string toTerminal() const noexcept;

private:
    command_t m_command;
    Type m_type = UNKNOWN;
};

std::string typeToString(const Type& type) noexcept;