# Require CMake 3.28 or newer and use its modern policy defaults.
cmake_minimum_required(VERSION 3.28)
# Name the project and enable C++ compiler support (CXX means C++).
project(cpp_learning LANGUAGES CXX)

# Load CMake's module for downloading and building dependencies.
include(FetchContent)

# Store SFML options as persistent boolean cache entries; FORCE overrides previous values.
# Disable SFML's audio module because this application does not use it.
set(SFML_BUILD_AUDIO OFF CACHE BOOL "" FORCE)
# Disable SFML's networking module for the same reason.
set(SFML_BUILD_NETWORK OFF CACHE BOOL "" FORCE)

# Describe where to obtain SFML and pin it to version 3.1.0.
# GIT_SHALLOW avoids downloading the full repository history.
# EXCLUDE_FROM_ALL builds dependency targets only when needed by our targets.
# SYSTEM treats dependency include directories as system headers, reducing their warnings.
FetchContent_Declare(SFML
  GIT_REPOSITORY https://github.com/SFML/SFML.git
  GIT_TAG 3.1.0
  GIT_SHALLOW ON
  EXCLUDE_FROM_ALL
  SYSTEM
)

# Download SFML if necessary and make its CMake targets available to this project.
FetchContent_MakeAvailable(SFML)

# Request C++23 for targets created after this setting.
set(CMAKE_CXX_STANDARD 23)
# Fail configuration if the compiler cannot provide the requested standard.
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Use standard C++ mode rather than a compiler-specific dialect such as gnu++23.
set(CMAKE_CXX_EXTENSIONS OFF)
# Treat compiler warnings as errors for targets created after this setting.
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

# Obtain a pinned Catch2 release with the same download/build/header options as SFML.
FetchContent_Declare(Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.8.1
  GIT_SHALLOW ON
  EXCLUDE_FROM_ALL
  SYSTEM
)
# Download Catch2 if necessary and expose its targets, including its supplied test main().
FetchContent_MakeAvailable(Catch2)

# Run clang-tidy when compiling our subsequently created targets.
# Disable other checks, enable include-cleaner, and make its findings build errors.
# This comes after dependency setup so their targets do not inherit this command.
set(CMAKE_CXX_CLANG_TIDY
  clang-tidy
  --checks=-*,misc-include-cleaner
  --warnings-as-errors=misc-include-cleaner
)

# Collect chess implementation files recursively into CHESS_SOURCES.
# CONFIGURE_DEPENDS asks the build system to detect additions/removals and reconfigure.
# CMAKE_CURRENT_SOURCE_DIR is the directory containing this CMakeLists.txt.
file(GLOB_RECURSE CHESS_SOURCES CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/src/chess/*.cpp"
)

# Compile chess code into a static library that both executables can link into themselves.
add_library(chess STATIC ${CHESS_SOURCES})
# PUBLIC supplies this header search path to chess and to targets linking against chess.
target_include_directories(chess PUBLIC
  "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

# Collect GUI implementation files separately so they do not become part of the chess library.
file(GLOB_RECURSE GUI_SOURCES CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/src/gui/*.cpp"
)

# Build the graphical executable from its entry point and GUI implementation files.
add_executable(application src/main.cpp ${GUI_SOURCES})
# Link the chess library and SFML graphics; PRIVATE keeps these requirements local.
target_link_libraries(application PRIVATE chess SFML::Graphics)

# Apply the existing Homebrew LLVM linking configuration only when targeting Linux.
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  # Tell the linker where to search for libraries when building the application.
  target_link_directories(application PRIVATE
    "/home/linuxbrew/.linuxbrew/opt/llvm/lib"
  )

  # Embed a runtime library search path in the executable used from the build directory.
  set_target_properties(application PROPERTIES
    BUILD_RPATH "/home/linuxbrew/.linuxbrew/opt/llvm/lib"
  )
  # Retain libgcc_s even without direct symbol references, then restore linker state.
  # -Wl, forwards flags to the linker; SHELL: keeps this option group together.
  target_link_options(application PRIVATE
    "SHELL:-Wl,--push-state,--no-as-needed -lgcc_s -Wl,--pop-state"
  )
# End the application's Linux-only configuration.
endif()

# Collect project headers for a separate include-cleaner check.
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
)

# Create a custom build target that checks headers without producing an output file.
# -p points clang-tidy at the build directory's compilation database.
# Extra arguments select C++ header parsing and C++23; COMMENT labels the build step.
# VERBATIM lets CMake escape command arguments correctly for the build tool.
add_custom_target(check_headers
  COMMAND ${CMAKE_CXX_CLANG_TIDY}
    -p "${CMAKE_CURRENT_BINARY_DIR}"
    --extra-arg=-xc++-header
    --extra-arg=-std=c++23
    ${HEADERS}
  COMMENT "Checking header includes with clang-tidy"
  VERBATIM
)
# Run the header-check target whenever the application target is built.
add_dependencies(application check_headers)

# Apply the same warning options to both the application and the chess library.
foreach(target IN ITEMS application chess)
  # PRIVATE applies these flags to this target's compilation without propagating them.
  target_compile_options(${target} PRIVATE
    -Wall                 # Enable a broad set of common warnings (not every warning).
    -Wextra               # Enable additional warnings beyond -Wall.
    -Wpedantic            # Warn about extensions outside the selected C++ standard.
    -Wconversion          # Warn about implicit conversions that may change values.
    -Wsign-conversion     # Warn about implicit signed/unsigned conversions.
    -Wunused-parameter    # Warn when a function parameter is unused.
    -Wshadow              # Warn when a declaration hides another declaration.
    -Wmissing-prototypes  # Warn about applicable functions without prior declarations.
  )
# End the loop over the two targets.
endforeach()

# Allow application sources to include headers relative to src.
target_include_directories(application PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

# Enable test registration so CTest can discover tests from this build directory.
enable_testing()

# Collect test sources recursively and reconfigure when files are added or removed.
file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp"
)

# Build all test files into one executable using Catch2's main().
add_executable(chess_tests ${TEST_SOURCES})

# Supply chess implementations and Catch2's assertions, test runner, and main().
target_link_libraries(chess_tests PRIVATE chess Catch2::Catch2WithMain)

# Apply the same existing Linux executable linking configuration to the test runner.
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  # Search Homebrew LLVM's library directory when linking the tests.
  target_link_directories(chess_tests PRIVATE
    "/home/linuxbrew/.linuxbrew/opt/llvm/lib"
  )

  # Let the built test executable find these shared libraries at runtime.
  set_target_properties(chess_tests PROPERTIES
    BUILD_RPATH "/home/linuxbrew/.linuxbrew/opt/llvm/lib"
  )

  # Retain libgcc_s and restore the previous linker state afterward, as for application.
  target_link_options(chess_tests PRIVATE
    "SHELL:-Wl,--push-state,--no-as-needed -lgcc_s -Wl,--pop-state"
  )
# End the test runner's Linux-only configuration.
endif()

# Register one CTest test that runs the executable; Catch2 runs the TEST_CASEs inside it.
add_test(NAME chess_tests COMMAND chess_tests)
