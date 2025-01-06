#ifndef ANIMATOR_HPP
#define ANIMATOR_HPP
#include <map>

#include "Animation.hpp"

class Animator {
public:
  Animator(std::map<std::string, Animation>, float fps);

  void setAnimation(std::string name);
  std::string getAnimation() const;
  void update(sf::Time dt);
  sf::IntRect getFrame() const;

private:
  std::map<std::string, Animation> _animations;
  std::string _currentAnimation;
  float _fps;
  float _accumulator;
  int _frame;
};
#endif //ANIMATOR_HPP
