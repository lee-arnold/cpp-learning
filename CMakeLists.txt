cmake_minimum_required(VERSION 3.28)
project(cpp_learning LANGUAGES CXX)

include(FetchContent)

set(SFML_BUILD_AUDIO OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_NETWORK OFF CACHE BOOL "" FORCE)

FetchContent_Declare(SFML
  GIT_REPOSITORY https://github.com/SFML/SFML.git
  GIT_TAG 3.1.0
  GIT_SHALLOW ON
  EXCLUDE_FROM_ALL
  SYSTEM
)

FetchContent_MakeAvailable(SFML)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

set(CMAKE_CXX_CLANG_TIDY
  clang-tidy
  --checks=-*,misc-include-cleaner
  --warnings-as-errors=misc-include-cleaner
)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_executable(application ${SOURCES})
target_link_libraries(application PRIVATE SFML::Graphics)

file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
)

add_custom_target(check_headers
  COMMAND ${CMAKE_CXX_CLANG_TIDY}
    -p "${CMAKE_CURRENT_BINARY_DIR}"
    --extra-arg=-xc++-header
    --extra-arg=-std=c++23
    ${HEADERS}
  COMMENT "Checking header includes with clang-tidy"
  VERBATIM
)
add_dependencies(application check_headers)

target_compile_options(application PRIVATE
  -Wall
  -Wextra
  -Wpedantic
  -Wconversion
  -Wsign-conversion
  -Wunused-parameter
  -Wshadow
  -Wmissing-prototypes
)

target_include_directories(application PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/src"
)
