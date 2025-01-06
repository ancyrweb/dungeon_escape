#include <iostream>
#include <map>
#include <SFML/Graphics.hpp>

#include "Animation.hpp"
#include "GameConfig.hpp"
#include "Player.hpp"
#include "TerrainBlock.hpp"

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

  std::vector<std::unique_ptr<Character>> gameObjects;
  gameObjects.push_back(std::make_unique<Player>(map));

  std::array<std::array<std::unique_ptr<TerrainBlock>, GameConfig::MAP_WIDTH>, GameConfig::MAP_HEIGHT> terrainBlocks;
  terrainBlocks[5][5] = std::make_unique<TerrainBlock>(true, sf::Vector2i(5, 5));

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

      for (auto& go : gameObjects) {
        go->input(event.value());
      }
    }

    for (auto& go : gameObjects) {
      go->update(dt);
    }

    window.clear(sf::Color::White);

    for (const auto& row : terrainBlocks) {
      for (const auto& block : row) {
        if (block != nullptr) {
          block->draw(window);
        }
      }
    }

    for (const auto& go : gameObjects) {
      go->draw(window);
    }

    window.display();
  }

  return 0;
}
