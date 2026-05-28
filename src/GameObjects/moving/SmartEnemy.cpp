#include "GameObjects/moving/SmartEnemy.h"
#include "GameObjects/moving/Player.h"
#include "Board.h"
#include "Utilities/SpeedSettings.h"
#include "Utilities/Helpers.h"
#include <cmath>

SmartEnemy::SmartEnemy(const sf::Texture &texture, sf::Vector2f startPos, Board& board)
    : Enemy(texture, startPos), m_board(board) {
    m_parents.resize(Helpers::toIndex(static_cast<int>(m_board.getHeight())), 
                     std::vector<sf::Vector2i>(Helpers::toIndex(static_cast<int>(m_board.getWidth())), {-1, -1}));
}

size_t SmartEnemy::toIndex(int coord) {
    return Helpers::toIndex(coord);
}

void SmartEnemy::move(float deltaTime) {
    MovingObject::move(deltaTime);

    if (!m_board.hasPlayer()) {
        return;
    }

    // BFS Pathfinding
    sf::Vector2f desiredDirection = getNextMoveBFS(m_board.getPlayerRef());
    
    if (m_isOnLadder && std::abs(desiredDirection.x) > Consts::Enemy::Smart::DIRECTION_EPSILON && 
        std::abs(desiredDirection.y) < Consts::Enemy::Smart::DIRECTION_EPSILON) {
        desiredDirection = handleLadderAlignment(desiredDirection);
    }

    m_direction = desiredDirection;

    sf::Vector2f movement = m_direction * SpeedSettings::SMART_ENEMY_SPEED * deltaTime;

    moveTo(getPosition() + movement);

    if (m_isOnLadder && std::abs(desiredDirection.y) > Consts::Enemy::Smart::DIRECTION_EPSILON && 
        std::abs(desiredDirection.x) < Consts::Enemy::Smart::DIRECTION_EPSILON) {
        centerHorizontalOnTile();
    }
}

sf::Vector2f SmartEnemy::getNextMoveBFS(const Player& player) const {
    const int rows = static_cast<int>(m_board.getHeight());
    const int cols = static_cast<int>(m_board.getWidth());

    const sf::Vector2i startNode(static_cast<int>(getBounds().getCenter().x / Consts::TILE_SIZE),
                           static_cast<int>(getBounds().getCenter().y / Consts::TILE_SIZE));

    const sf::Vector2i targetNode(static_cast<int>(player.getBounds().getCenter().x / Consts::TILE_SIZE),
                            static_cast<int>(player.getBounds().getCenter().y / Consts::TILE_SIZE));

    if (startNode.x < 0 || startNode.x >= cols || startNode.y < 0 || startNode.y >= rows ||
        targetNode.x < 0 || targetNode.x >= cols || targetNode.y < 0 || targetNode.y >= rows) {
        return {0.f, 0.f};
    }

    if (startNode == targetNode) {
        return {0.f, 0.f};
    }

    const ParentsTable& parents = runBFS(startNode, targetNode);

    return findFirstStep(parents, startNode, targetNode);
}

const SmartEnemy::ParentsTable& SmartEnemy::runBFS(sf::Vector2i startLocation, sf::Vector2i targetLocation) const {
    for (auto& row : m_parents) {
        std::fill(row.begin(), row.end(), sf::Vector2i(-1, -1));
    }

    std::queue<sf::Vector2i> q;

    q.push(startLocation);
    m_parents[toIndex(startLocation.y)][toIndex(startLocation.x)] = {-2, -2};

    sf::Vector2i directions[] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    while (!q.empty()) {
        sf::Vector2i current = q.front();
        q.pop();

        if (current == targetLocation) {
            return m_parents;
        }

        for (sf::Vector2i dir: directions) {
            handleNeighbor(current, dir, m_parents, q);
        }
    }

    return m_parents;
}

void SmartEnemy::handleNeighbor(sf::Vector2i current, sf::Vector2i dir,
                                ParentsTable &parents, std::queue<sf::Vector2i> &q) const {
    sf::Vector2i next = current + dir;
    int rows = static_cast<int>(parents.size());
    int cols = static_cast<int>(parents[0].size());

    if (next.x < 0 || next.y < 0 || next.x >= cols || next.y >= rows) return;

    if (parents[toIndex(next.y)][toIndex(next.x)] != sf::Vector2i(-1, -1)) return;

    if (!isMoveValid(current, next, dir)) {
        return;
    }

    parents[toIndex(next.y)][toIndex(next.x)] = current;
    q.push(next);
}

sf::Vector2f SmartEnemy::findFirstStep(const ParentsTable &parents, sf::Vector2i start, sf::Vector2i target) const {
    sf::Vector2i curr = target;

    if (parents[toIndex(curr.y)][toIndex(curr.x)] == sf::Vector2i(-1, -1)) {
        return {0.f, 0.f};
    }

    while (parents[toIndex(curr.y)][toIndex(curr.x)] != start) {
        curr = parents[toIndex(curr.y)][toIndex(curr.x)];
        if (curr == sf::Vector2i(-1, -1)) {
            return {0.f, 0.f};
        }
    }

    return sf::Vector2f(static_cast<float>((curr.x - start.x)),
                        static_cast<float>((curr.y - start.y)));
}

bool SmartEnemy::isMoveValid(sf::Vector2i current, sf::Vector2i next, sf::Vector2i dir) const {
    char currentTile = m_board.getCharAt(current.x, current.y);
    char nextTile = m_board.getCharAt(next.x, next.y);

    if (nextTile == '#' || nextTile == '^' || nextTile == '\0') {
        return false;
    }

    if ((dir.y == -1 || dir.y == 1) && currentTile != 'H') {
        return false;
    }

    if (dir.y == -1 && nextTile != 'H' && nextTile != '-') {
        return false;
    }

    return true;
}

sf::Vector2f SmartEnemy::handleLadderAlignment(sf::Vector2f desiredDirection) {
    int currentTileY = static_cast<int>(getPosition().y / Consts::TILE_SIZE);
    
    // Always aim for the vertical center of the current row.
    float targetY = (currentTileY * Consts::TILE_SIZE) + (Consts::TILE_SIZE / 2.f);
    
    float diff = getPosition().y - targetY;
    
    if (diff > Consts::Enemy::Smart::VERTICAL_ALIGNMENT_TOLERANCE) {
        return {0.f, -1.f};
    } else if (diff < -Consts::Enemy::Smart::VERTICAL_ALIGNMENT_TOLERANCE) {
        return {0.f, 1.f};
    } else {
        setPosition(getPosition().x, targetY);
        return desiredDirection;
    }
}