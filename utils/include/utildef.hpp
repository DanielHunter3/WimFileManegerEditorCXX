/*
 Only macros and constexpr
*/

#pragma once

// Макросы первого порядка

#define VOID std::nullopt

#define ResultError(err, msg) std::unexpected(Error {err, msg})
#define OptionError(err, msg) Error {err, msg}

#define FM_ELEMENT_NOT_FOUND(cmd, p) std::string {cmd} + " : The path \"" + p + "\" cannot be found because it does not exist"
#define FM_ELEMENT_IS_EXISTS(cmd, p) std::string {cmd} + " The element with the specified name \"" + p + "\" already exists"

// Макросы второго порядка

// Конкретный тип ошибок
#define OptionFSError(str, name, e) OptionError(EnumError::FileSystemError, std::string {str} + " (" + name + ") : " + e.what())
#define ResultFSError(str, name, e) ResultError(EnumError::FileSystemError, std::string {str} + " (" + name + ") : " + e.what())

#define OptionNotFoundError(str, name) OptionError(EnumError::NotFoundError, FM_ELEMENT_NOT_FOUND(str, name))
#define ResultNotFoundError(str, name) ResultError(EnumError::NotFoundError, FM_ELEMENT_NOT_FOUND(str, name))
//---

// Макросы для автоматической проверки и преобразования типв VOption
#define ResultErrorFrom(e) std::unexpected(e)

#define IfOptionByResultError(f) if (auto value = f; value != VOID) return ResultErrorFrom(value.value())
#define IfOptionByOptionError(f) if (auto value = f; value != VOID) return value.value();
//---