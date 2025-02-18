#include "header/resulthandler.hpp"

const TypeOfError ResultError::type() const noexcept {
    return m_type;
}

const std::string ResultError::message() const noexcept {
    return m_message;
}