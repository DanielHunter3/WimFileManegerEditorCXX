#pragma once

#include <expected>
#include <optional>

template <typename E>
class StructError {
 public:
  StructError(E type, std::string message)
   : m_type(std::move(type)), m_message(std::move(message)) {}
  StructError() = delete;

  E type() const noexcept {
   return m_type;
  }
  [[nodiscard]] const std::string& message() const noexcept {
   return m_message;
  }

 private:
  E m_type;
  std::string m_message;
};

enum class EnumError {
 RangeOutError,
 InvalidArgumentError,
 FileReadError,
 FileWriteError,
 ElementDeleteError,
 ElementCreateError,
 DataFoundError,
 ChangeDirectoryError,
 EmptyCommandError,
 ExitCommandError,
 ChmodError,
 FileSystemError,
 UnknownError,
 NotFoundError,
};

using Error = StructError<EnumError>;

template <typename T>
using UResult = std::expected<T, Error>;

using VOption = std::optional<Error>;