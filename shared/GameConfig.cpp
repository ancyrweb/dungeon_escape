#include "GameConfig.hpp"

int GameConfig::getTileSize() {
  return 40;
}

sf::Vector2i GameConfig::getMapSize() {
  return { 20, 20 };
}