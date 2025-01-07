#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <SFML/Graphics.hpp>

#include "Animator.hpp"
#include "TerrainMap.hpp"

class Character {
public:
  Character(std::map<std::string, Animation> animations);
  virtual ~Character() = default;

  virtual void input(const sf::Event &event, const TerrainMap &terrainMap) {}
  virtual void update(const sf::Time& dt);
  virtual void draw(sf::RenderWindow& window) const;

  sf::Vector2f getPosition() const { return _sprite.getPosition(); }
  sf::Vector2i getCoordinates() const;

protected:
  sf::Vector2f closestAvailablePosition(const sf::Vector2f &target) const;
  void setTarget(sf::Vector2i position, const TerrainMap &terrainMap);
  void updateTarget(const sf::Time& dt);

protected:
  Animator _animator;
  sf::Texture _texture;
  sf::Sprite _sprite;

  sf::Vector2f _targetPosition;
  bool _reachedTarget;

  sf::Vector2i _velocityVector;
  float _velocityFactor;
};

#endif //GAMEOBJECT_HPP
