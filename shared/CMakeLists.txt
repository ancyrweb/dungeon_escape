add_library(shared STATIC GameConfig.cpp GameConfig.hpp)

target_include_directories(shared PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})