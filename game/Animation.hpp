#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <SFML/Graphics.hpp>

class Animation {
public:
  Animation(sf::Vector2i position, sf::Vector2i sizePerTile, int frameCount);

  sf::IntRect getFrame(int frame) const;
  int getFrameCount() const;

private:
  sf::Vector2i _position;
  sf::Vector2i _sizePerTile;
  int _frameCount;
};
#endif //ANIMATION_HPP
