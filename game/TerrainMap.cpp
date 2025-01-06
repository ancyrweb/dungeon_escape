
#include "TerrainMap.hpp"

TerrainMap::TerrainMap() {
  _map[5][5] = std::make_unique<TerrainBlock>(true, sf::Vector2i(5, 5));
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