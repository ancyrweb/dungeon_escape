#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <list>
#include <SFML/Graphics.hpp>

#include "Animator.hpp"
#include "PathFinder.hpp"

class Character {
public:
  Character(std::map<std::string, Animation> animations, const PathFinder &pathFinder);
  virtual ~Character() = default;

  virtual void input(const sf::Event &event) {}
  virtual void update(const sf::Time& dt);
  virtual void draw(sf::RenderWindow& window) const;

  sf::Vector2f getPosition() const { return _sprite.getPosition(); }
  sf::Vector2i getCoordinates() const;

protected:
  void setTarget(sf::Vector2i position);
  void updateTarget(const sf::Time& dt);

protected:
  const PathFinder &_pathFinder;

  Animator _animator;
  sf::Texture _texture;
  sf::Sprite _sprite;

  std::list<sf::Vector2f> _path;

  sf::Vector2i _velocityVector;
  float _velocityFactor;
};

#endif //GAMEOBJECT_HPP
