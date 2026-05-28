#include "GameObjects/parents/GameObject.h"
#include "GameObjects/parents/StaticObject.h"
#include "GameObjects/moving/Player.h"
#include "GameObjects/moving/Enemy.h"

StaticObject::StaticObject(const sf::Texture& texture, GameObjects objectType)
    : GameObject(texture, Buttons::Max, objectType) {}

void StaticObject::handleCollision(Player& other) {
    handleCollision(static_cast<MovingObject&>(other));
}

void StaticObject::handleCollision(Enemy& other) {
    handleCollision(static_cast<MovingObject&>(other));
}