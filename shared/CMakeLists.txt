add_library(shared STATIC GameConfig.cpp GameConfig.hpp
)

target_link_libraries(shared PRIVATE SFML::Graphics)
target_include_directories(shared PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})