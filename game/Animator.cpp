#include "Animator.hpp"

#include <iostream>

Animator::Animator(std::map<std::string, Animation> animations, float fps)
  : _currentAnimation(animations.begin()->first),
  _animations(animations),
  _fps(fps),
  _accumulator(0),
  _frame(0) {
  assert(!_animations.empty() && "Animator initialized with empty animations map!");
}

void Animator::setAnimation(std::string name) {
  _currentAnimation = name;
  _accumulator = 0;
  _frame = 0;
}

std::string Animator::getAnimation() const {
  return _currentAnimation;
}

void Animator::update(sf::Time dt) {
  if (_animations.find(_currentAnimation) == _animations.end()) {
    throw std::runtime_error("Invalid animation key: " + _currentAnimation);
  }

  auto *it = &_animations.at(_currentAnimation);

  if (it->getFrameCount() == 1) {
    return;
  }

  _accumulator += dt.asMilliseconds();

  if (_accumulator >= _fps) {
    _accumulator = 0;
    _frame++;

    if (_frame > it->getFrameCount()) {
      _frame = 0;
    }
  }
}

sf::IntRect Animator::getFrame() const {
  return _animations.at(_currentAnimation).getFrame(_frame);
}