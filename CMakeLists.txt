cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(psql_test VERSION 0.1)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Finding System Deps
find_package(fmt REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTEST REQUIRED gtest)
pkg_check_modules(PQXX REQUIRED libpqxx)

#set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -ggdb -Og -Wall -Wextra -Werror -include cstddef -fdiagnostics-color=always")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2 -Wall -Wextra -Werror -include cstddef -fdiagnostics-color=always")

# for use with clang tidy and clang format
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_program(CLANG_TIDY NAMES "clang-tidy")
set(CLANG_TIDY_COMMAND "${CLANG_TIDY}" "--config-file=${PROJECT_SOURCE_DIR}/.clang-tidy")

find_program(CLANG_FORMAT NAMES "clang-format")
set(CLANG_FORMAT_COMMAND "${CLANG_FORMAT}") # default is `--style=file`, where it looks for `.clang-format` in parent dir

#add_subdirectory(dep)
add_subdirectory(src)

option(BUILD_TESTS OFF)
if (BUILD_TESTS)
    add_subdirectory(test)
endif()

message("")
message("========================")
message("CONFIG")
message("========================")
message("CMAKE_SYSTEM_NAME:       ${CMAKE_SYSTEM_NAME}")
message("CMAKE_SYSTEM_VERSION:    ${CMAKE_SYSTEM_VERSION}")
message("CMAKE_BINARY_DIR:        ${CMAKE_BINARY_DIR}")
message("CMAKE_INSTALL_PREFIX:    ${CMAKE_INSTALL_PREFIX}")
message("CMAKE_SYSTEM_PROCESSOR:  ${CMAKE_SYSTEM_PROCESSOR}")
message("CMAKE_C_COMPILER:        ${CMAKE_C_COMPILER}")
message("CMAKE_CXX_COMPILER:      ${CMAKE_CXX_COMPILER}")
message("CMAKE_BUILD_TYPE:        ${CMAKE_BUILD_TYPE}")
message("CMAKE_INSTALL_LIBDIR:    ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
message("")
 
