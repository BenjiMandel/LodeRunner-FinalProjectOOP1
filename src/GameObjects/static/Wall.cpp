#include "GameObjects/static/Wall.h"
#include "GameObjects/parents/StaticObject.h"
#include "GameObjects/parents/MovingObject.h"

Wall::Wall(const sf::Texture& texture)
    : StaticObject(texture, GameObjects::Wall) {}

void Wall::handleCollision(GameObject& other) {
    other.handleCollision(*this);
}

void Wall::handleCollision(MovingObject& other) {
    other.handleCollision(*this);
}
