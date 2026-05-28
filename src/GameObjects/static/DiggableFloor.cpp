#include "GameObjects/static/DiggableFloor.h"
#include "GameObjects/parents/MovingObject.h"

DiggableFloor::DiggableFloor(const sf::Texture& texture)
    : StaticObject(texture, GameObjects::DiggableFloor), m_isHole(false) {}

void DiggableFloor::dig() {
    // If it's already a hole, do nothing
    if (m_isHole) return;

    m_isHole = true;

    // Make the floor invisible (visual trick)
    getSprite().setColor(sf::Color::Transparent);
}

bool DiggableFloor::isHole() const {
    return m_isHole;
}

void DiggableFloor::handleCollision(GameObject& other) {
    other.handleCollision(*this);
}

void DiggableFloor::handleCollision(MovingObject& other) {
    other.handleCollision(*this);
}
