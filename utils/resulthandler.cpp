// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "header/resulthandler.hpp"

const TypeOfError ResultError::type() const noexcept {
    return m_type;
}

const std::string& ResultError::message() const noexcept {
    return m_message;
}