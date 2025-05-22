cmake_minimum_required(VERSION 3.10)

project(WimEditorFileManagerApp CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(NOT CMAKE_BUILD_TYPE)
 set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -Werror")
set(CMAKE_CXX_FLAGS_DEBUG "-Og")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

include_directories(${PROJECT_SOURCE_DIR}/utils/include)
include_directories(${PROJECT_SOURCE_DIR}/include)

# Используем GLOB_RECURSE для поиска всех .cpp файлов
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE UTILS "utils/src/*.cpp")

add_executable(WimEditorFileManagerApp "src/main.cpp" ${SOURCES} ${UTILS})
