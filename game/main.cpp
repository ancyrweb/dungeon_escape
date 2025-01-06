#include <iostream>
#include <map>
#include <SFML/Graphics.hpp>

#include "Animation.hpp"
#include "GameConfig.hpp"
#include "Player.hpp"

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
        { "idleDown", {{ 0, 0 }, { 120, 130 }, 1 }},
        { "idleLeft", {{ 0, 130 }, { 120, 130 }, 1 }},
        { "idleUp", {{ 0, 260 }, { 120, 130 }, 1 }},
        { "idleRight", {{ 0, 390 }, { 120, 130 }, 1 }},
        { "walkingDown", {{ 0, 520 }, { 120, 130 }, 9 }},
        { "walkingLeft", {{ 0, 650 }, { 120, 130 }, 9 }},
        { "walkingUp", {{ 0, 780 }, { 120, 130 }, 9 }},
        { "walkingRight", {{ 0, 910 }, { 120, 130 }, 9 }}
  };

  Player player = Player(map);

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

      player.input(event.value());
    }

    player.update(dt);
    window.clear(sf::Color::White);

    player.draw(window);
    window.display();
  }

  return 0;
}
