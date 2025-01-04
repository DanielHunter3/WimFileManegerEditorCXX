#pragma once

#include <vector>
#include <string>
#include <variant>

using command_t = std::variant<std::vector<std::string>, std::string>;

enum Type {
    STR, VECSTR, UNKNOWN
};

class FMObject {
public:
    FMObject(const command_t& command);
    FMObject(void);
    ~FMObject();

    Type setType() const noexcept;
    std::string toTerminal() const noexcept;
    void getObject(const command_t&);

private:
    command_t m_command;
    Type m_type = UNKNOWN;
};

std::string typeToString(const Type& type) noexcept;