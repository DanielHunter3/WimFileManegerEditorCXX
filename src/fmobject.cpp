// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <map>
#include <memory>

#include "header/fmobject.hpp"

FMObject::FMObject(const Universal& command)
    : m_command(command)
{
    if (std::holds_alternative<std::string>(command)) m_type = STR;
    else if (std::holds_alternative<std::vector<std::string>>(command)) m_type = VECSTR;
    else m_type = UNKNOWN;
}
FMObject::FMObject(void) = default;
FMObject::~FMObject() = default;

Type FMObject::setType() const noexcept { return m_type; }
std::string FMObject::toTerminal() const noexcept {
    if (m_type == VECSTR) {
        auto result = std::make_unique<std::string>();
        for (const auto& arg : std::get<std::vector<std::string>>(m_command)) {
            *result += arg + "\n";
        }
        return result->substr(0, result->size() - 1);
    }
    return std::get<std::string>(m_command);
}
void FMObject::getObject(const Universal& command) {
    m_command = command;
    if (std::holds_alternative<std::string>(command)) m_type = STR;
    else if (std::holds_alternative<std::vector<std::string>>(command)) m_type = VECSTR;
    else m_type = UNKNOWN;
}

std::string typeToString(const Type& type) noexcept { 
    auto map = std::make_unique<std::map<Type, std::string>>();
    *map = {
        {STR, "STR"},
        {VECSTR, "VECSTR"},
        {UNKNOWN, "UNKNOWN"},
    };
    return (*map)[type];
}