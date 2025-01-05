cmake_minimum_required(VERSION 3.30)
project(DungeonEscape)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add shared library
add_subdirectory(shared)

# Add executables
add_subdirectory(editor)
add_subdirectory(game)