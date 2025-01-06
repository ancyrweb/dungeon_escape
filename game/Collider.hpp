
#ifndef COLLIDER_HPP
#define COLLIDER_HPP
#include "WorldContext.hpp"

class Collider {
public:
  void check(WorldContext &worldContext, const sf::Time &dt);
private:
  void check(WorldContext &worldContext, const sf::Time &dt, Character &character);
};
#endif //COLLIDER_HPP
