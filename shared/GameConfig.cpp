#include "GameConfig.hpp"

int GameConfig::getTileSize() {
  return TILE_SIZE;
}

sf::Vector2i GameConfig::getMapSize() {
  return { MAP_WIDTH, MAP_HEIGHT };
}