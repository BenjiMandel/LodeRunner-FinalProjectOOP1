#include "GameObjects/static/Rope.h"
#include "GameObjects/parents/MovingObject.h"

Rope::Rope(const sf::Texture& texture)
    : StaticObject(texture, GameObjects::Rope) {}

void Rope::handleCollision(GameObject& other) {
    other.handleCollision(*this);
}

void Rope::handleCollision(MovingObject& other) {
    other.handleCollision(*this);
}
