#include "GameObjects/moving/Player.h"
#include "Board.h"
#include "Utilities/SpeedSettings.h"
#include "GameObjects/static/Coin.h"
#include "GameObjects/static/Wall.h"
#include "GameObjects/static/Ladder.h"
#include "GameObjects/static/DiggableFloor.h"
#include "GameObjects/static/Rope.h"
#include "GameObjects/moving/Enemy.h"
#include "GameObjects/parents/MovingObject.h"
#include "Utilities/Consts.h"
#include "Utilities/Helpers.h"
#include "Types/BoardSymbols.h"

Player::Player(const sf::Texture& texture, sf::Vector2f startPos, Board& board)
    : MovingObject(texture, startPos), m_wasFalling(false), m_board(board) {
}

void Player::move(float deltaTime) {
    if (m_isDead) {
        m_deathAnimationTimer += deltaTime;
        if (m_deathAnimationTimer < Consts::Player::DEATH_ANIMATION_DURATION) {
            getSprite().rotate(sf::degrees(Consts::Player::DEATH_ROTATION_SPEED * deltaTime));
        }
        return;
    }

    const bool canClimb = m_isOnLadder || m_isOnRope;

    MovingObject::move(deltaTime);
    float step = SpeedSettings::PLAYER_SPEED * deltaTime;
    sf::Vector2f movement = handleInput(step, canClimb);
    if (!Helpers::isZero(movement)) {
        moveTo(getSprite().getPosition() + movement);
    }
}

sf::Vector2f Player::handleInput(float step, bool canClimb) {
    sf::Vector2f movement(0.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        movement.x -= step;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        movement.x += step;
    }
    if (canClimb) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
            float feetY = getPosition().y - step + getBounds().size.y / 2.0f;
            int gridX = static_cast<int>(getPosition().x / Consts::TILE_SIZE);
            int gridY = static_cast<int>((feetY - Consts::Player::TILE_CHECK_OFFSET) / Consts::TILE_SIZE);
            char tile = m_board.getCharAt(gridX, gridY);
            if (tile == BoardSymbols::Ladder || tile == BoardSymbols::Rope || tile == BoardSymbols::DiggableFloor) {
                movement.y -= step;
            }
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
            if (m_isOnRope) {
                m_isOnRope = false;
            } else {
                movement.y += step;
            }
        }
    }
    return movement;
}

void Player::resetToStartPosition() {
    MovingObject::resetToStartPosition();

    m_isDead = false;
    m_deathAnimationTimer = 0.0f;
    m_wasFalling = false;
    getSprite().setRotation(sf::degrees(0));
}

bool Player::isDead() const {
    return m_isDead;
}

void Player::kill() {
    if (!m_isDead) {
        m_isDead = true;
        m_deathAnimationTimer = 0.0f;
    }
}

// --- Handle Collisions ---

// Double dispatch entry point
void Player::handleCollision(GameObject& other) {
    other.handleCollision(*this);
}

// Wall collision
void Player::handleCollision(Wall& other) {
    MovingObject::handleCollision(other);
}

// DiggableFloor collision
void Player::handleCollision(DiggableFloor& other) {
    if (other.isHole()) {
        return;
    }
    MovingObject::handleCollision(other);
}

// Ladder collision
void Player::handleCollision(Ladder& other) {
    MovingObject::handleCollision(other);
}

// Rope collision
void Player::handleCollision(Rope& other) {
    MovingObject::handleCollision(other);
}

// Coin collision
void Player::handleCollision(Coin& other) {
    other.handleCollision(*this);
}

// Enemy collision
void Player::handleCollision(Enemy& /*other*/) {
    kill();
}