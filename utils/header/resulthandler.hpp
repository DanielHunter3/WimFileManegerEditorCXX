#pragma once

#include <string>
#include <variant>

#ifdef __unix__
    #include <stdexcept>
#endif

enum TypeOfError {
    FILE_ERROR,
    MEMORY_ERROR,
    NETWORK_ERROR,
    TYPE_ERROR,
    ZERO_ERROR,
    //...
};

struct ThisError {
    TypeOfError error;
    std::string message;
};

class ResultError {
public:
    ResultError(const TypeOfError&& error, const std::string&& message)
        : m_error(error), m_message(message) {}
    ResultError(const TypeOfError&& error)
        : m_error(error), m_message("No information") {}

    ThisError value() const;

private:
    TypeOfError m_error;
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
        : m_value(value) {}
    Result(const T&& value) 
        : m_value(value) {}

    Result(ResultError&& error)
        : m_value(error) {}

    constexpr bool is_error() const noexcept {
        return std::holds_alternative<ResultError>(m_value);
    }
    constexpr bool is_ok() const noexcept { 
        return std::holds_alternative<T>(m_value);
    }

    const T& ok() const {
        return std::get<T>(m_value);
    }
    const ResultError& error() const {
        return std::get<ResultError>(m_value);
    }

    const T unwrap() const {
        if (std::holds_alternative<ResultError>(m_value)) {
            throw std::runtime_error(error().value().message);
        }
        return std::get<T>(m_value);
    }

    const T except(std::string&& message) const  {
        if (std::holds_alternative<ResultError>(m_value)) {
            throw std::runtime_error(std::move(message));
        }
        return std::get<T>(m_value);
    }

    constexpr ResultType type() const noexcept {
        return (std::holds_alternative<T>(m_value) ? ResultType::Ok : ResultType::Error);
    }

private:
    std::variant<T, ResultError> m_value;
};