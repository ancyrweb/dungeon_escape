#include "Player.hpp"

#include <iostream>

#include "GameConfig.hpp"

Player::Player(std::map<std::string, Animation> animations) :
  Character(animations)
{
  _isSettingTarget = false;
  _currentTile.setSize({
    static_cast<float>(GameConfig::getTileSize()),
    static_cast<float>(GameConfig::getTileSize())
  });
  _currentTile.setFillColor(sf::Color(255, 0, 0, 100));
  alignCurrentTile();
}

void Player::input(const sf::Event &event) {
  if (const auto* mouseButtonPressed = event.getIf<sf::Event::MouseButtonPressed>()) {
    if (mouseButtonPressed->button == sf::Mouse::Button::Right) {
      _isSettingTarget = true;
      setTarget(mouseButtonPressed->position);
    }
  }

  if (const auto* mouseButtonReleased = event.getIf<sf::Event::MouseButtonReleased>()) {
    if (mouseButtonReleased->button == sf::Mouse::Button::Right) {
      _isSettingTarget = false;
    }
  }

  if (_isSettingTarget) {
    if (const auto* mouseMoved = event.getIf<sf::Event::MouseMoved>()) {
      setTarget(mouseMoved->position);
    }
  }
}

void Player::update(const sf::Time &dt) {
  Character::update(dt);
  alignCurrentTile();
}

void Player::draw(sf::RenderWindow &window) const {
  window.draw(_currentTile);
  Character::draw(window);
}

void Player::alignCurrentTile() {
  auto coordinates = getCoordinates();

  sf::Vector2f position = {
    static_cast<float>(coordinates.x * GameConfig::getTileSize()),
    static_cast<float>(coordinates.y * GameConfig::getTileSize())
  };

  _currentTile.setPosition(position);
}
