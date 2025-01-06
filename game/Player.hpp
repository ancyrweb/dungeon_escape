#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <map>
#include <SFML/Graphics.hpp>

#include "Animation.hpp"
#include "Character.hpp"

class Player : public Character {
public:
  explicit Player(std::map<std::string, Animation> animations);
  void input(const sf::Event& event) override;
  void update(const sf::Time &dt) override;
  void draw(sf::RenderWindow &window) const override;

private:
  bool _isSettingTarget;
  sf::RectangleShape _currentTile;
  void alignCurrentTile();
};

#endif //PLAYER_HPP
