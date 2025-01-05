
#ifndef GAMECONFIG_HPP
#define GAMECONFIG_HPP

#include <SFML/Graphics.hpp>

class GameConfig {
  public:
    static int getTileSize();
    static sf::Vector2i getMapSize();
};

#endif //GAMECONFIG_HPP
