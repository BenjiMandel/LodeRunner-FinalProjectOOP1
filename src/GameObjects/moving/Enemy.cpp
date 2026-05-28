#include "GameObjects/moving/Enemy.h"
#include "GameObjects/moving/Player.h"
#include "GameObjects/static/Wall.h"
#include "GameObjects/static/DiggableFloor.h"
#include "GameObjects/static/Ladder.h"
#include "GameObjects/static/Rope.h"

Enemy::Enemy(const sf::Texture& texture, sf::Vector2f startPos)
    : MovingObject(texture, startPos) {}


// --- handle Collisions ---

// Double dispatch entry point.
void Enemy::handleCollision(GameObject& other) {
    other.handleCollision(*this);
}

// Wall collision: delegate to MovingObject.
void Enemy::handleCollision(Wall& other) {
    MovingObject::handleCollision(other);
}

// DiggableFloor collision: delegate to MovingObject.
void Enemy::handleCollision(DiggableFloor& other) {
    // Ignore collision with holes - enemies can fall through
    if (other.isHole()) {
        return;
    }

    MovingObject::handleCollision(other);
}

// Ladder collision: delegate to MovingObject.
void Enemy::handleCollision(Ladder& other) {
    MovingObject::handleCollision(other);
}

// Rope collision: delegate to MovingObject.
void Enemy::handleCollision(Rope& other) {
    MovingObject::handleCollision(other);
}

void Enemy::handleCollision(Player& other) {
    other.handleCollision(*this);
}

// Handle collision with another enemy.
void Enemy::handleCollision(Enemy& other) {
    handleObstacle(other);
}
