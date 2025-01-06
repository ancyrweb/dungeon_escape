#include "Player.hpp"
#include "GameConfig.hpp"

#include <cmath>

Player::Player(std::map<std::string, Animation> animations) :
  _animator(animations, 60.0f),
  _texture("../../assets/characters/player.png"),
  _sprite(_texture),
  _targetPosition(0, 0),
  _reachedTarget(true),
  _isSettingTarget(false),
  _velocityVector(0, 0),
  _velocityFactor(100.0f)
{
  _sprite.setScale({ (float) GameConfig::getTileSize() / 120.0f, (float) GameConfig::getTileSize() / 130.0f });
  _sprite.setTextureRect(_animator.getFrame());
  _sprite.setPosition({ 400, 300 });
  _targetPosition = _sprite.getPosition();
}

void Player::initialize() {
  _animator.setAnimation("idleDown");
}

void Player::input(const sf::Event &event) {
  inputTargetPosition(event);
}

void Player::inputTargetPosition(const sf::Event &event) {
  if (const auto* mouseButtonPressed = event.getIf<sf::Event::MouseButtonPressed>()) {
    if (mouseButtonPressed->button == sf::Mouse::Button::Right) {
      _isSettingTarget = true;

      auto bounds = _sprite.getGlobalBounds();
      _targetPosition.x = mouseButtonPressed->position.x - bounds.size.x / 2;
      _targetPosition.y = mouseButtonPressed->position.y - bounds.size.y / 2;
      _reachedTarget = false;
    }
  }

  if (const auto* mouseButtonReleased = event.getIf<sf::Event::MouseButtonReleased>()) {
    if (mouseButtonReleased->button == sf::Mouse::Button::Right) {
      _isSettingTarget = false;
    }
  }

  if (_isSettingTarget) {
    if (const auto* mouseMoved = event.getIf<sf::Event::MouseMoved>()) {
      auto bounds = _sprite.getGlobalBounds();
      _targetPosition.x = mouseMoved->position.x - bounds.size.x / 2;
      _targetPosition.y = mouseMoved->position.y - bounds.size.y / 2;
      _reachedTarget = false;
    }
  }
}

void Player::update(const sf::Time &dt) {
  _animator.update(dt);
  _sprite.setTextureRect(_animator.getFrame());

  updateTarget(dt);
}

void Player::updateTarget(const sf::Time& dt) {
  auto position = _sprite.getPosition();

  if (_reachedTarget == false) {
    const auto deltaX = std::fabs(position.x - _targetPosition.x);
    const auto deltaY = std::fabs(position.y - _targetPosition.y);
    constexpr float area = 5.0f;

    float movX = 0.0f;
    float movY = 0.0f;

    if (deltaX > area) {
      if (position.x < _targetPosition.x) {
        movX += _velocityFactor * dt.asSeconds();
      } else if (position.x > _targetPosition.x) {
        movX -= _velocityFactor * dt.asSeconds();
      }
    }

    if (deltaY > area) {
      if (position.y < _targetPosition.y) {
        movY += _velocityFactor * dt.asSeconds();
      } else if (position.y > _targetPosition.y) {
        movY -= _velocityFactor * dt.asSeconds();
      }
    }

    if (deltaX < area && deltaY < area) {
      position = _targetPosition;
      _reachedTarget = true;

      if (_animator.getAnimation() == "walkingRight") {
        _animator.setAnimation("idleRight");
      } else if (_animator.getAnimation() == "walkingLeft") {
        _animator.setAnimation("idleLeft");
      } else if (_animator.getAnimation() == "walkingDown") {
        _animator.setAnimation("idleDown");
      } else if (_animator.getAnimation() == "walkingUp") {
        _animator.setAnimation("idleUp");
      }
    } else {
      position.x += movX;
      position.y += movY;

      auto remaining = _targetPosition - position;

      if (std::fabs(remaining.x) > std::fabs(remaining.y)) {
        if (movX > 0) {
          _animator.setAnimation("walkingRight");
        } else {
          _animator.setAnimation("walkingLeft");
        }
      } else {
        if (movY > 0) {
          _animator.setAnimation("walkingDown");
        } else {
          _animator.setAnimation("walkingUp");
        }
      }
    }
  }

  _sprite.setPosition(position);
}

void Player::draw(sf::RenderWindow &window) const {
  window.draw(_sprite);
}