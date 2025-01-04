// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "header/customexception.hpp"

const char* ElementNotFoundException::what() const noexcept {
    return m_message;
}

const char* FileWriteException::what() const noexcept {
    return m_message;
}

const char* FileReadException::what() const noexcept  {
    return m_message;
}

const char* ElementDeleteException::what() const noexcept {
    return m_message;
}

const char* ElementCreateException::what() const noexcept {
    return m_message;
}

const char* ChangeDirectoryException::what() const noexcept {
    return m_message;
}

const char* UndefinedCommandException::what() const noexcept {
    return m_message;
}

const char* InvalidArgumentException::what() const noexcept {
    return m_message;
}

const char* EmptyCommandException::what() const noexcept {
    return m_message;
}