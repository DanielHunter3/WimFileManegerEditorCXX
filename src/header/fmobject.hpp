#pragma once

#include <vector>
#include <string>
#include <variant>

#include "commandhandler.hpp"

enum Type {
    STR, VECSTR, UNKNOWN
};

class FMObject {
public:
    FMObject(const Universal& command);
    FMObject(void);
    ~FMObject();

    Type setType() const noexcept;
    std::string toTerminal() const noexcept;
    void getObject(const Universal&);

private:
    Universal m_command;
    Type m_type = UNKNOWN;
};

std::string typeToString(const Type& type) noexcept;