
#include "TerrainBlock.hpp"

#include "GameConfig.hpp"

TerrainBlock::TerrainBlock() : _isSolid(false), _coordinates({ 0, 0 }) {
  synchronize();
}

TerrainBlock::TerrainBlock(bool isSolid, sf::Vector2i coordinates) : _isSolid(isSolid), _coordinates(coordinates) {
  synchronize();
}

void TerrainBlock::init(bool isSolid, sf::Vector2i coordinates) {
  _isSolid = isSolid;
  _coordinates = coordinates;
  synchronize();
}

void TerrainBlock::synchronize() {
  _shape.setSize(sf::Vector2f(GameConfig::getTileSize(), GameConfig::getTileSize()));
  _shape.setPosition({
    static_cast<float>(_coordinates.x * GameConfig::getTileSize()),
    static_cast<float>(_coordinates.y * GameConfig::getTileSize())
  });

  if (_isSolid) {
    _shape.setFillColor(sf::Color::Black);
    _shape.setOutlineColor(sf::Color(200, 200, 200));
    _shape.setOutlineThickness(1);
  } else {
    _shape.setFillColor(sf::Color(200, 200, 200));
  }
}

void TerrainBlock::draw(sf::RenderWindow &window) const {
  window.draw(_shape);
}
