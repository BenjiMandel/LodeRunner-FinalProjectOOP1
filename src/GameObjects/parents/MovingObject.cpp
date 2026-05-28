#include "GameObjects/parents/MovingObject.h"
#include "GameObjects/static/Wall.h"
#include "GameObjects/static/DiggableFloor.h"
#include "GameObjects/static/Rope.h"
#include "Utilities/SpeedSettings.h"
#include "Utilities/Consts.h"

MovingObject::MovingObject(const sf::Texture &texture, sf::Vector2f startPos)
    : GameObject(texture), m_startPosition(startPos), m_lastPosition(startPos) {
    sf::Vector2u size = texture.getSize();
    getSprite().setOrigin({ size.x / 2.0f, size.y / 2.0f });
    setPosition(m_startPosition);
}

MovingObject::~MovingObject() = default;

sf::Vector2f MovingObject::m_worldBounds = { static_cast<float>(Consts::WINDOW_WIDTH), static_cast<float>(Consts::GAME_HEIGHT) };

void MovingObject::setWorldBounds(sf::Vector2f bounds) {
    m_worldBounds = bounds;
}

void MovingObject::move(float deltaTime) {
    m_lastPosition = getPosition();

    if (!m_isOnGround && !m_isOnLadder && !m_isOnRope) {
        float fallDistance = SpeedSettings::GRAVITY_SPEED * deltaTime;
        sf::Vector2f currentPos = getPosition();
        sf::Vector2f nextPos(currentPos.x, currentPos.y + fallDistance);
        moveTo(nextPos);
    }
}

void MovingObject::moveTo(sf::Vector2f targetPos) {
    setDirection(targetPos.x - getSprite().getPosition().x);
    getSprite().setPosition(targetPos);
}

void MovingObject::resetPhysicsFlags() {
    m_isOnGround = false;
    m_isOnLadder = false;
    m_isOnRope = false;
}

void MovingObject::setDirection(float xDelta) {
    if (xDelta > Consts::Movement::DIRECTION_CHANGE_THRESHOLD) {
        getSprite().setScale({ 1.f, 1.f });
    }
    else if (xDelta < -Consts::Movement::DIRECTION_CHANGE_THRESHOLD) {
        getSprite().setScale({ -1.f, 1.f });
    }
}

bool MovingObject::isOnGround() const {
    return m_isOnGround;
}

void MovingObject::setOnGround(bool onGround) {
    m_isOnGround = onGround;
}

void MovingObject::returnToLastPosition() {
    setPosition(m_lastPosition);
}

void MovingObject::resetToStartPosition() {
    setPosition(m_startPosition);
    resetPhysicsFlags();
}

void MovingObject::centerHorizontalOnTile(float speedFactor) {
    sf::Vector2f currentPos = getPosition();
    int currentTileX = static_cast<int>(currentPos.x / Consts::TILE_SIZE);
    float tileCenterX = (static_cast<float>(currentTileX) * Consts::TILE_SIZE) + Consts::Movement::HALF_TILE_SIZE;
    float offsetX = tileCenterX - currentPos.x;

    if (std::abs(offsetX) > Consts::Movement::CENTERING_THRESHOLD) {
        setPosition(currentPos.x + offsetX * speedFactor, currentPos.y);
    }
}

sf::FloatRect MovingObject::getBounds() const {
    auto bounds = getSprite().getGlobalBounds();
    // Apply LADDER_HITBOX_BUFFER to make hitbox smaller
    if (m_isOnLadder) {
        bounds.position.x += Consts::Collision::LADDER_HITBOX_BUFFER;
        bounds.size.x -= 2 * Consts::Collision::LADDER_HITBOX_BUFFER;
    }
    return bounds;
}

// --- Collisions ---
void MovingObject::handleCollision(Wall& other) {
    handleObstacle(other);
}

void MovingObject::handleCollision(DiggableFloor& other) {
    if (m_isOnLadder || m_isOnRope) {
        return;
    }
    handleObstacle(other);
}

void MovingObject::handleObstacle(GameObject& other) {
    auto myBounds = getSprite().getGlobalBounds();
    auto otherBounds = other.getBounds();

    const float myHeight = myBounds.size.y;
    const float lastBottom = m_lastPosition.y + myHeight / 2.f;
    const float otherTop = otherBounds.position.y;

    if (lastBottom <= otherTop + Consts::Collision::GROUND_COLLISION_TOLERANCE) {
        // Ground snap offset to prevent jittering
        float newCenterY = otherTop - myHeight / 2.f + 2.0f;
        setPosition(getPosition().x, newCenterY);
        m_isOnGround = true;
    } else {
        returnToLastPosition();
    }
}

void MovingObject::handleCollision(Ladder& /*other*/) {
    m_isOnLadder = true;
}

void MovingObject::handleCollision(Rope& other) {
    auto otherBounds = other.getBounds();
    float ropeCenterY = otherBounds.position.y + otherBounds.size.y / 2.0f;
    float myCenterY = getPosition().y;

    // Rope alignment tolerance for grabbing
    if (std::abs(myCenterY - ropeCenterY) < Consts::Collision::ROPE_ALIGNMENT_TOLERANCE) {
        m_isOnRope = true;
        setPosition(getPosition().x, ropeCenterY);
    }
}