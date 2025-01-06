#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <map>
#include <SFML/Graphics.hpp>

#include "Animation.hpp"
#include "Animator.hpp"
#include "GameObject.hpp"

class Player : public GameObject {
public:
  explicit Player(std::map<std::string, Animation> animations);

  void initialize();
  void input(const sf::Event& event) override;
  void update(const sf::Time& dt) override;
  void draw(sf::RenderWindow& window) const override;

private:
  Animator _animator;
  sf::Texture _texture;
  sf::Sprite _sprite;

  sf::Vector2f _targetPosition;
  bool _reachedTarget;
  bool _isSettingTarget;

  sf::Vector2i _velocityVector;
  float _velocityFactor;

  void inputTargetPosition(const sf::Event& event);
  void updateTarget(const sf::Time& dt);
};

#endif //PLAYER_HPP
