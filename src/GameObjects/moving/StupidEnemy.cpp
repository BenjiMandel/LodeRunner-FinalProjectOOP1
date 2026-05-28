#include "GameObjects/moving/StupidEnemy.h"
#include "Utilities/SpeedSettings.h"
#include "Utilities/Consts.h"
#include <cstdlib>
#include <cmath>

StupidEnemy::StupidEnemy(const sf::Texture& texture, sf::Vector2f startPos)
    : Enemy(texture, startPos) {
    m_lastPos = getSprite().getPosition();
    chooseRandomDirection(false);
}

void StupidEnemy::move(float deltaTime) {
    const bool canClimb = m_isOnLadder;

    MovingObject::move(deltaTime);

    const sf::Vector2f currentPos = getSprite().getPosition();

    const bool isStuck = std::abs(currentPos.x - m_lastPos.x) < Consts::Enemy::Stupid::STUCK_THRESHOLD &&
        std::abs(currentPos.y - m_lastPos.y) < Consts::Enemy::Stupid::STUCK_THRESHOLD;

    if (isStuck || (!canClimb && std::abs(m_direction.y) > Consts::Enemy::Stupid::DIRECTION_THRESHOLD)) {
        chooseRandomDirection(canClimb);
    }

    m_lastPos = currentPos;

    sf::Vector2f movement = m_direction * SpeedSettings::STUPID_ENEMY_SPEED * deltaTime;

    moveTo(currentPos + movement);

    if (m_isOnLadder && std::abs(m_direction.y) > Consts::Enemy::Stupid::DIRECTION_THRESHOLD && 
        std::abs(m_direction.x) < Consts::Enemy::Stupid::DIRECTION_THRESHOLD) {
        centerHorizontalOnTile();
    }
}

void StupidEnemy::chooseRandomDirection(bool canClimb) {
    if (!canClimb) {
        int dir = rand() % 2;

        if (dir == 0) m_direction = { 1.f, 0.f };
        else          m_direction = { -1.f, 0.f };

        return;
    }

    int dir = rand() % 4;

    switch (dir) {
    case 0: m_direction = { 1.f, 0.f }; break;
    case 1: m_direction = { -1.f, 0.f }; break;
    case 2: m_direction = { 0.f, 1.f }; break;
    case 3: m_direction = { 0.f, -1.f }; break;
    }
}