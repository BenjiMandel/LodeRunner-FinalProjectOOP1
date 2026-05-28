#include "GameObjects/static/Ladder.h"
#include "GameObjects/parents/MovingObject.h"

Ladder::Ladder(const sf::Texture& texture)
    : StaticObject(texture, GameObjects::Ladder) {}

void Ladder::handleCollision(GameObject& other) {
    other.handleCollision(*this);
}

void Ladder::handleCollision(MovingObject& other) {
    other.handleCollision(*this);
}
