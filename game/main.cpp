#include <iostream>
#include <map>
#include <SFML/Graphics.hpp>

#include "Animation.hpp"
#include "AnimationKeys.hpp"
#include "Collider.hpp"
#include "GameConfig.hpp"
#include "Player.hpp"
#include "TerrainBlock.hpp"
#include "WorldContext.hpp"

int main() {
  auto mapSize = GameConfig::getMapSize();
  auto tileSize = GameConfig::getTileSize();

  sf::RenderWindow window(sf::VideoMode({
    static_cast<unsigned int>(mapSize.x) * tileSize,
      static_cast<unsigned int>(mapSize.y) * tileSize
  }), "Dungeon Escape");

  window.setKeyRepeatEnabled(false);
  window.setFramerateLimit(60);

  auto map = std::map<std::string, Animation>{
        { AnimationKeys::IDLE_DOWN, {{ 0, 0 }, { 120, 130 }, 1 }},
        { AnimationKeys::IDLE_LEFT, {{ 0, 130 }, { 120, 130 }, 1 }},
        { AnimationKeys::IDLE_UP, {{ 0, 260 }, { 120, 130 }, 1 }},
        { AnimationKeys::IDLE_RIGHT, {{ 0, 390 }, { 120, 130 }, 1 }},
        { AnimationKeys::WALKING_DOWN, {{ 0, 520 }, { 120, 130 }, 9 }},
        { AnimationKeys::WALKING_LEFT, {{ 0, 650 }, { 120, 130 }, 9 }},
        { AnimationKeys::WALKING_UP, {{ 0, 780 }, { 120, 130 }, 9 }},
        { AnimationKeys::WALKING_RIGHT, {{ 0, 910 }, { 120, 130 }, 9 }}
  };

  std::vector<std::unique_ptr<Character>> characters;
  characters.push_back(std::make_unique<Player>(map));

  TerrainMap terrainMap;
  WorldContext worldContext(characters, terrainMap);
  Collider collider;

  sf::Clock clock;

  while (window.isOpen()) {
    sf::Time dt = clock.restart();

    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      } else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
        if (keyPressed->code == sf::Keyboard::Key::Escape) {
          window.close();
        }
      }

      for (auto& c : characters) c->input(event.value());
    }

    for (auto& c : characters) c->update(dt);
    collider.check(worldContext, dt);

    window.clear(sf::Color::White);

    terrainMap.draw(window);
    for (const auto& c : characters) c->draw(window);

    window.display();
  }

  return 0;
}
