#pragma once

#include <string>
#include <variant>
#include <cstdlib>
#include <iostream>

#define PANIC_MEM 505

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

class ResultError {
public:
    ResultError(const TypeOfError&& type, const std::string&& message)
        : m_type(type), m_message(message) {}
    ResultError(const TypeOfError&& type)
        : m_type(type), m_message("No information") {}

    const TypeOfError type() const noexcept;
    const std::string& message() const noexcept;

private:
    TypeOfError m_type;
    std::string m_message;
};

template <typename T>
class Result {
public:
    enum ResultType {
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
            throw std::runtime_error(error().message());
        }
        return std::get<T>(m_value);
    }

    /*
    Unwraps the Result and returns the contained value.
    If the Result is an error, it will throw the exception.
    */
    const T ok() const {
        return std::get<T>(m_value);
    }
    /*
    Unwraps the Result and returns the contained value.
    If the Result is not an error, it will throw the exception.
    */
    const ResultError error() const {
        return std::get<ResultError>(m_value);
    }

    /*
    Unwraps the Result and returns the contained value. 
    If the Result is an error, it will print an error message and exit with code 505.
    */
    const T unwrap() const noexcept {
        if (std::holds_alternative<ResultError>(m_value)) {
            std::cerr << std::endl << error().message() << std::endl;
            exit(PANIC_MEM);
        }
        return std::get<T>(m_value);
    }

    /* 
    @param message the message to print if Result failed

    Unwraps the Result and returns the contained value. 
    If the Result is an error, it will print an error message and exit with code 505.
    */
    const T except(std::string&& message) const noexcept  {
        if (std::holds_alternative<ResultError>(m_value)) {
            std::cerr << std::endl << message << std::endl;
            exit(PANIC_MEM);
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