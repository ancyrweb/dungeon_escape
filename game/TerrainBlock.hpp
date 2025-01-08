
#ifndef TERRAINBLOCK_HPP
#define TERRAINBLOCK_HPP

#include <SFML/Graphics.hpp>

class TerrainBlock {
public:
  TerrainBlock();
  TerrainBlock(const TerrainBlock &other);
  TerrainBlock(bool isSolid, sf::Vector2i coordinates);

  bool isSolid() { return _isSolid; }

  void init(bool isSolid, sf::Vector2i coordinates);
  void draw(sf::RenderWindow& window) const;
private:
  bool _isSolid;
  sf::Vector2i _coordinates;
  sf::RectangleShape _shape;

  void synchronize();
};
#endif //TERRAINBLOCK_HPP
