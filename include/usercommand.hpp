#pragma once

#include <vector>
#include <string>

#include "fmobject.hpp"

UResult<FMObject> getFMObject(const std::vector<std::string>&) noexcept;