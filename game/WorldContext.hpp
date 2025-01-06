#ifndef WORLDCONTEXT_HPP
#define WORLDCONTEXT_HPP

#include "Character.hpp"
#include "GameConfig.hpp"
#include "TerrainBlock.hpp"
#include "TerrainMap.hpp"

class WorldContext {
public:
  WorldContext(std::vector<std::unique_ptr<Character>> &characters, TerrainMap &terrainMap) :
    _characters(characters),
    _terrainMap(terrainMap)
  {}

  std::vector<std::unique_ptr<Character>>& getCharacters() {
    return _characters;
  }

  TerrainMap &getTerrainMap() {
    return _terrainMap;
  }
private:
  std::vector<std::unique_ptr<Character>>& _characters;
  TerrainMap &_terrainMap;
};

#endif //WORLDCONTEXT_HPP
