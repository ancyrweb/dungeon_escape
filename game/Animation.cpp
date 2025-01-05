#include "Animation.hpp"

#include <iostream>

Animation::Animation(sf::Vector2i position, sf::Vector2i sizePerTile, int frameCount)
  : _position(position),
  _sizePerTile(sizePerTile),
  _frameCount(frameCount) {
}

sf::IntRect Animation::getFrame(int frame) const {
  return sf::IntRect(
    { _position.x + frame * _sizePerTile.x, _position.y },
    { _sizePerTile.x, _sizePerTile.y }
    );
}

int Animation::getFrameCount() const {
  return _frameCount;
}