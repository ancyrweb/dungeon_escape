#include "Player.hpp"

#include "GameConfig.hpp"

Player::Player(std::map<std::string, Animation> animations) :
  _animator(animations, 60.0f),
  _texture("../../assets/characters/player.png"),
  _sprite(_texture)
{
  _sprite.setScale({ (float) GameConfig::getTileSize() / 120.0f, (float) GameConfig::getTileSize() / 130.0f });
  _sprite.setTextureRect(_animator.getFrame());
  _sprite.setPosition({ 400, 300 });
}

void Player::initialize() {
  _animator.setAnimation("idleDown");
}

void Player::input(const sf::Event &event) {
  if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
    if (keyPressed->code == sf::Keyboard::Key::Q) {
      _animator.setAnimation("walkingLeft");
    } else if (keyPressed->code == sf::Keyboard::Key::S) {
      _animator.setAnimation("walkingDown");
    } else if (keyPressed->code == sf::Keyboard::Key::Z) {
      _animator.setAnimation("walkingUp");
    } else if (keyPressed->code == sf::Keyboard::Key::D) {
      _animator.setAnimation("walkingRight");
    }
  } else if (const auto* keyReleased = event.getIf<sf::Event::KeyReleased>()) {
    if (keyReleased->code == sf::Keyboard::Key::Q) {
      if (_animator.getAnimation() == "walkingLeft") {
        _animator.setAnimation("idleLeft");
      }
    } else if (keyReleased->code == sf::Keyboard::Key::S) {
      if (_animator.getAnimation() == "walkingDown") {
        _animator.setAnimation("idleDown");
      }
    } else if (keyReleased->code == sf::Keyboard::Key::Z) {
      if (_animator.getAnimation() == "walkingUp") {
        _animator.setAnimation("idleUp");
      }
    } else if (keyReleased->code == sf::Keyboard::Key::D) {
      if (_animator.getAnimation() == "walkingRight") {
        _animator.setAnimation("idleRight");
      }
    }
  }
}

void Player::update(const sf::Time &dt) {
  _animator.update(dt);
  _sprite.setTextureRect(_animator.getFrame());
}

void Player::draw(sf::RenderWindow &window) const {
  window.draw(_sprite);
}