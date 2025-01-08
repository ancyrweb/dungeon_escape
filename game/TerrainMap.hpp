#ifndef TERRAINMAP_HPP
#define TERRAINMAP_HPP
#include "GameConfig.hpp"
#include "TerrainBlock.hpp"

typedef std::array<std::array<std::unique_ptr<TerrainBlock>, GameConfig::MAP_WIDTH>, GameConfig::MAP_HEIGHT> TerrainMapArray;

class TerrainMap {
public:
  TerrainMap();
  TerrainMapArray &getMap() { return _map; }
  bool isSolid(sf::Vector2i coordinates) const;
  void draw(sf::RenderWindow &window) const;
private:
  TerrainMapArray _map;
};

#endif //TERRAINMAP_HPP
