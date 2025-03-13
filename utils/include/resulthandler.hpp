#pragma once

#include <string>
#include <variant>
#include <cstdlib>
#include <iostream>

enum TypeOfError {
    RangeOutError,
    UnknownElementError,
    InvalidArgumentError,
    FileReadError,
    ElementDeleteError,
    ElementCreateError,
    DataFoundError,
    ElementRenameError,
    ElementCopyError,
    FileWriteError,
    ChangeDirectoryError,
    EmptyCommandError,
    //...
};

class ResultException : std::exception {
public:
    ResultException(const char* message): message_(message) {}
    ResultException(const std::string& message): message_(message.c_str()) {}
    const char* what() const noexcept override { return message_; }
private:
    const char* message_;
};

class ResultError {
public:
    ResultError(const TypeOfError&& type, const std::string&& message)
        : m_type(type), m_message(message) {}
    ResultError(const TypeOfError&& type)
        : m_type(type), m_message("No information") {}

    TypeOfError type() const noexcept;
    const std::string& message() const noexcept;

private:
    TypeOfError m_type;
    std::string m_message;
};

template <typename T>
class Result {
public:
    enum class ResultType {
        Ok,
        Error
    };

    Result(const T& value) 
        : m_value(std::move(value)) {}
    Result(const T&& value) 
        : m_value(std::move(value)) {}

    Result(const ResultError&& error)
        : m_value(std::move(error)) {}

    constexpr bool is_error() const noexcept {
        return std::holds_alternative<ResultError>(m_value);
    }
    constexpr bool is_ok() const noexcept { 
        return std::holds_alternative<T>(m_value);
    }

    const T& operator*() const {
        if (std::holds_alternative<ResultError>(m_value)) {
            throw ResultException(error().message());
        }
        return std::get<T>(m_value);
    }
    /*
    Unwraps the Result and returns the contained value.
    If the Result is not an error, it will throw the exception.
    */
    const ResultError error() const {
        if (std::holds_alternative<T>(m_value)) {
            throw ResultException("Object is not error");
        }
        return std::get<ResultError>(m_value);
    }

    const T unwrap() const {
        if (std::holds_alternative<ResultError>(m_value)) {
            throw ResultException(error().message());
        }
        return std::get<T>(m_value);
    }

    const T except(std::string&& message) const {
        if (std::holds_alternative<ResultError>(m_value)) {
            throw ResultException(message);
        }
        return std::get<T>(m_value);
    }

    /*
    Returns Ok if the Result contains a value, Error otherwise.
    */
    constexpr ResultType type() const noexcept {
        return (std::holds_alternative<T>(m_value) ? ResultType::Ok : ResultType::Error);
    }

private:
    std::variant<T, ResultError> m_value;
};