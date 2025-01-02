#pragma once

#include <exception>

class ElementNotFoundException : public std::exception {
private:
    const char* m_message;
public:
    ElementNotFoundException(const char* message) : m_message(message) {}
    const char* what() const noexcept override;
};

class FileWriteException : public std::exception {
private:
    const char* m_message;
public:
    FileWriteException(const char* message) : m_message(message) {}
    const char* what() const noexcept override;
};

class FileReadException : public std::exception {
public:
    FileReadException(const char* message) : m_message(message) {}
    const char* what() const noexcept override;
private:
    const char* m_message;
};

class ElementDeleteException : public std::exception {
public:
    ElementDeleteException(const char* message) : m_message(message) {}
    const char* what() const noexcept override;
private:
    const char* m_message;
};

class ElementCreateException : public std::exception {
public:
    ElementCreateException(const char* message) : m_message(message) {}
    const char* what() const noexcept override;
private:
    const char* m_message;
};

class ChangeDirectoryException : public std::exception {
public:
    ChangeDirectoryException(const char* message) : m_message(message) {}
    const char* what() const noexcept override;
private:
    const char* m_message;
};