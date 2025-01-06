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

private:
  bool _isSettingTarget;
};

#endif //PLAYER_HPP
