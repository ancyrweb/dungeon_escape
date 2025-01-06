#include "Collider.hpp"

#include <iostream>

void Collider::check(WorldContext &worldContext, const sf::Time &dt) {
  auto &terrainMap = worldContext.getTerrainMap();
  auto &terrainArray = terrainMap.getMap();

  for (auto &c : worldContext.getCharacters()) {
    check(worldContext, dt, *c);
  }
}

void Collider::check(WorldContext &worldContext, const sf::Time &dt, Character &character) {
  // Check against terrain
  auto position = character.getPosition();


}

