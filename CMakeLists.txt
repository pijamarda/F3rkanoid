cmake_minimum_required(VERSION 3.16)
# The game version lives in the VERSION file (bumped by release.sh).
file(STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/VERSION" F3RKANOID_VERSION LIMIT_COUNT 1)
project(F3rkanoid VERSION ${F3RKANOID_VERSION} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# When cross-compiling with MinGW (Docker Windows build), SFML is installed
# as static archives so we must tell find_package to look for the -s targets.
if(MINGW)
    set(SFML_STATIC_LIBRARIES TRUE)
endif()

file(GLOB SOURCES "source/*.cpp")
add_executable(f3rkanoid ${SOURCES})

target_compile_definitions(f3rkanoid PRIVATE F3RKANOID_VERSION="${F3RKANOID_VERSION}")

find_package(SFML 2.5 COMPONENTS graphics window system audio REQUIRED)
target_link_libraries(f3rkanoid PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
)

# Embed the MinGW C++ runtime so the .exe has no libstdc++/libgcc DLL deps.
if(MINGW)
    target_link_options(f3rkanoid PRIVATE -static-libgcc -static-libstdc++)
endif()
