add_executable(game main.cpp
        Animation.cpp
        Animation.hpp
        Animator.cpp
        Animator.hpp
        Player.cpp
        Player.hpp
        Character.hpp
        TerrainBlock.cpp
        TerrainBlock.hpp
        Character.cpp
        AnimationKeys.hpp
        TerrainMap.cpp
        TerrainMap.hpp
        PathFinder.cpp
        PathFinder.hpp
)

target_link_libraries(game PRIVATE SFML::Graphics shared)
target_include_directories(game PRIVATE ${CMAKE_SOURCE_DIR}/shared)