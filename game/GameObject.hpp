#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <SFML/Graphics.hpp>

class GameObject {
public:
  virtual ~GameObject() = default;

  virtual void input(const sf::Event &event) {};
  virtual void update(const sf::Time& dt) = 0;
  virtual void draw(sf::RenderWindow& window) const = 0;
};

#endif //GAMEOBJECT_HPP
