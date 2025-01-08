#include "PathFinder.hpp"

#include <queue>

namespace std {
  template <>
  struct hash<sf::Vector2i> {
    std::size_t operator()(const sf::Vector2i& v) const noexcept {
      return std::hash<int>()(v.x) ^ (std::hash<int>()(v.y) << 1);
    }
  };
}

struct Node {
  sf::Vector2i coordinates;
  float cost;
  float heuristic;
  Node* parent;

  Node(sf::Vector2i coordinates, float cost, float heuristic, Node* parent = nullptr)
    : coordinates(coordinates), cost(cost), heuristic(heuristic), parent(parent) {}

  float totalCost() const {
    return cost + heuristic;
  }

  bool operator>(const Node& other) const {
    return totalCost() > other.totalCost();
  }
};

std::list<sf::Vector2f> PathFinder::findPath(sf::Vector2i startCoordinates, sf::Vector2f endPosition) const {
  std::list<sf::Vector2f> path;
  path.push_back(endPosition);

  sf::Vector2i endCoordinates(
    static_cast<int>(endPosition.x / GameConfig::TILE_SIZE),
    static_cast<int>(endPosition.y / GameConfig::TILE_SIZE)
  );

  auto heuristic = [](sf::Vector2i a, sf::Vector2i b) {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);
  };

  std::priority_queue<Node, std::vector<Node>, std::greater<Node>> openList;
  std::unordered_map<sf::Vector2i, Node*> allNodes;

  openList.emplace(startCoordinates, 0.0f, heuristic(startCoordinates, endCoordinates));
  allNodes[startCoordinates] = new Node(startCoordinates, 0.0f, heuristic(startCoordinates, endCoordinates));

  while (!openList.empty()) {
    Node current = openList.top();
    openList.pop();

    if (current.coordinates == endCoordinates) {
      Node* node = &current;
      while (node) {
        path.push_front(
          sf::Vector2f(
            node->coordinates.x * GameConfig::TILE_SIZE,
            node->coordinates.y * GameConfig::TILE_SIZE
          )
        );

        node = node->parent;
      }
      break;
    }

    std::vector<sf::Vector2i> neighbors = {
      {current.coordinates.x + 1, current.coordinates.y},
      {current.coordinates.x - 1, current.coordinates.y},
      {current.coordinates.x, current.coordinates.y + 1},
      {current.coordinates.x, current.coordinates.y - 1}
    };

    for (const auto& neighbor : neighbors) {
      if (_terrainMap.isSolid(neighbor)) continue;

      float newCost = current.cost + 1.0f;
      if (allNodes.find(neighbor) == allNodes.end() || newCost < allNodes[neighbor]->cost) {
        float h = heuristic(neighbor, endCoordinates);
        Node* neighborNode = new Node(neighbor, newCost, h, allNodes[current.coordinates]);
        openList.push(*neighborNode);
        allNodes[neighbor] = neighborNode;
      }
    }
  }

  for (auto& pair : allNodes) {
    delete pair.second;
  }

  return path;
}
