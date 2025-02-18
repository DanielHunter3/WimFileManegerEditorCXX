#pragma once

#include <vector>
#include <string>

#include "fmobject.hpp"
#include "communist.hpp"

Result<FMObject> getFMObject(const std::vector<std::string>&) noexcept;