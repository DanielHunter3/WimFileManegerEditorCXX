// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <map>
#include <memory>

#include "header/fmobject.hpp"

FMCommand::FMCommand(const std::vector<std::string>& command)
    : m_command(command), m_type(VECSTR) {}
FMCommand::FMCommand(const std::string& command)
    : m_command(command), m_type(STR) {}
FMCommand::~FMCommand() = default;

Type FMCommand::setType() const noexcept { return m_type; }
std::string FMCommand::toTerminal() const noexcept {
    if (m_type == VECSTR) {
        std::unique_ptr<std::string> result(new std::string);
        for (const auto& arg : std::get<std::vector<std::string>>(m_command)) {
            *result += arg + " ";
        }
        return result->substr(0, result->size() - 1);
    }
    return std::get<std::string>(m_command);
}

std::string typeToString(const Type& type) noexcept { 
    std::unique_ptr<std::map<Type, std::string>> map(new std::map<Type, std::string>);
    *map = {
        {STR, "STR"},
        {VECSTR, "VECSTR"},
        {UNKNOWN, "UNKNOWN"},
    };
    return (*map)[type];
}