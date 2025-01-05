#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <map>
#include <SFML/Graphics.hpp>

#include "Animation.hpp"
#include "Animator.hpp"
#include "GameObject.hpp"

class Player : public GameObject {
public:
  explicit Player(const std::map<std::string, Animation>& animations);

  void initialize();
  void input(const sf::Event& event) override;
  void update(const sf::Time& dt) override;
  void draw(sf::RenderWindow& window) const override;

private:
  std::map<std::string, Animation> _animations;
  Animator _animator;
  sf::Texture _texture;
  sf::Sprite _sprite;
};

#endif //PLAYER_HPP
