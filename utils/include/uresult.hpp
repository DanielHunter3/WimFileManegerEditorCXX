#pragma once

#include "result.hpp"

enum class EnumError {
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
};

template <typename T>
using UResult =  Result<T, EnumError>;

// template <typename T>
// using UResult =  UResult<T, StructError>;