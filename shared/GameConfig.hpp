
#ifndef GAMECONFIG_HPP
#define GAMECONFIG_HPP

#include <SFML/Graphics.hpp>

class GameConfig {
  public:
    static int getTileSize();
    static sf::Vector2i getMapSize();

    static constexpr int TILE_SIZE = 40;
    static constexpr int MAP_WIDTH = 20;
    static constexpr int MAP_HEIGHT = 20;
};

#endif //GAMECONFIG_HPP
