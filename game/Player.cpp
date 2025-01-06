#include "Player.hpp"
#include "GameConfig.hpp"

Player::Player(std::map<std::string, Animation> animations) :
  Character(animations)
{
  _isSettingTarget = false;
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


