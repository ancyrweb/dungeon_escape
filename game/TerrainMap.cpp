
#include "TerrainMap.hpp"

TerrainMap::TerrainMap() {
  _map[5][5] = std::make_unique<TerrainBlock>(true, sf::Vector2i(5, 5));
  _map[5][6] = std::make_unique<TerrainBlock>(true, sf::Vector2i(5, 6));
  _map[5][7] = std::make_unique<TerrainBlock>(true, sf::Vector2i(5, 7));
  _map[5][8] = std::make_unique<TerrainBlock>(true, sf::Vector2i(5, 8));
}

void TerrainMap::draw(sf::RenderWindow &window) const {
  for (const auto& row : _map) {
    for (const auto& block : row) {
      if (block) {
        block->draw(window);
      }
    }
  }
}

bool TerrainMap::isSolid(sf::Vector2i coordinates) const {
  if (coordinates.y < 0 || coordinates.y >= GameConfig::MAP_HEIGHT || coordinates.x < 0 || coordinates.x >= GameConfig::MAP_WIDTH) {
    return true;
  }

  auto block = _map[coordinates.y][coordinates.x].get();
  if (block == nullptr) {
    return false;
  }

  return block->isSolid();
}
