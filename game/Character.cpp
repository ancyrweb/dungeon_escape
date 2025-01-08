#include "Character.hpp"

#include <cmath>

#include "AnimationKeys.hpp"
#include "GameConfig.hpp"

Character::Character(std::map<std::string, Animation> animations, const PathFinder &pathFinder) :
  _pathFinder(pathFinder),
  _animator(animations, 60.0f),
  _texture("../../assets/characters/player.png"),
  _sprite(_texture),
  _velocityVector(0, 0),
  _velocityFactor(100.0f)
{
 auto frame = _animator.getFrame();

  _sprite.setScale({
    (float) GameConfig::getTileSize() / frame.size.x,
      (float) GameConfig::getTileSize() / frame.size.y
  });

  _sprite.setTextureRect(frame);
  _sprite.setPosition({ 400, 300 });
}

void Character::update(const sf::Time &dt) {
  _animator.update(dt);
  _sprite.setTextureRect(_animator.getFrame());

  updateTarget(dt);
}


void Character::draw(sf::RenderWindow &window) const {
  window.draw(_sprite);
}

sf::Vector2i Character::getCoordinates() const {
  auto position = _sprite.getPosition();
  auto size = _sprite.getGlobalBounds().size;

  int x = static_cast<int>(position.x + size.x / 2);
  int y = static_cast<int>(position.y + size.y / 2);

  return { x / GameConfig::getTileSize(), y / GameConfig::getTileSize() };
}

void Character::setTarget(sf::Vector2i position) {
  auto bounds = _sprite.getGlobalBounds();
  sf::Vector2f targetPosition(position.x - bounds.size.x / 2, position.y - bounds.size.y / 2);

  _path = _pathFinder.findPath(getCoordinates(), targetPosition);
}

void Character::updateTarget(const sf::Time& dt) {
  auto position = _sprite.getPosition();

  if (!_path.empty()) {
    constexpr float TARGET_AREA_EPSILON = 5.0f;
    auto target = _path.front();

    const auto deltaX = std::fabs(position.x - target.x);
    const auto deltaY = std::fabs(position.y - target.y);

    float movX = 0.0f;
    float movY = 0.0f;

    if (deltaX > TARGET_AREA_EPSILON) {
      if (position.x < target.x) {
        movX += _velocityFactor * dt.asSeconds();
      } else if (position.x > target.x) {
        movX -= _velocityFactor * dt.asSeconds();
      }
    }

    if (deltaY > TARGET_AREA_EPSILON) {
      if (position.y < target.y) {
        movY += _velocityFactor * dt.asSeconds();
      } else if (position.y > target.y) {
        movY -= _velocityFactor * dt.asSeconds();
      }
    }

    if (deltaX < TARGET_AREA_EPSILON && deltaY < TARGET_AREA_EPSILON) {
      position = target;
      _path.pop_front();

      if (_path.empty()) {
        if (_animator.getAnimation() == AnimationKeys::WALKING_RIGHT) {
          _animator.setAnimation(AnimationKeys::IDLE_RIGHT);
        } else if (_animator.getAnimation() == AnimationKeys::WALKING_LEFT) {
          _animator.setAnimation(AnimationKeys::IDLE_LEFT);
        } else if (_animator.getAnimation() == AnimationKeys::WALKING_DOWN) {
          _animator.setAnimation(AnimationKeys::IDLE_DOWN);
        } else if (_animator.getAnimation() == AnimationKeys::WALKING_UP) {
          _animator.setAnimation(AnimationKeys::IDLE_UP);
        }
      }
    } else {
      position.x += movX;
      position.y += movY;

      auto remaining = target - position;

      if (std::fabs(remaining.x) > std::fabs(remaining.y)) {
        if (movX > 0) {
          _animator.setAnimation(AnimationKeys::WALKING_RIGHT);
        } else {
          _animator.setAnimation(AnimationKeys::WALKING_LEFT);
        }
      } else {
        if (movY > 0) {
          _animator.setAnimation(AnimationKeys::WALKING_DOWN);
        } else {
          _animator.setAnimation(AnimationKeys::WALKING_UP);
        }
      }
    }
  }

  _sprite.setPosition(position);
}

