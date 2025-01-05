#include <iostream>
#include <SFML/Graphics.hpp>

int main() {
  sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Dungeon Escape");
  sf::CircleShape player(50);  // Example player shape
  player.setFillColor(sf::Color::Green);

  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      } else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
        if (keyPressed->code == sf::Keyboard::Key::Escape) {
          window.close();
        }
      }
    }

    window.clear();
    window.draw(player);  // Render player
    window.display();
  }

  return 0;
}