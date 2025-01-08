
#ifndef PATHFINDER_HPP
#define PATHFINDER_HPP
#include <list>

#include "TerrainMap.hpp"

class PathFinder {
public:
  PathFinder(const TerrainMap& terrainMap) : _terrainMap(terrainMap) {}

  std::list<sf::Vector2f> findPath(sf::Vector2i startCoordinates, sf::Vector2f endPosition) const;

private:
  const TerrainMap& _terrainMap;
};
#endif //PATHFINDER_HPP
