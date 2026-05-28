#include "GameObjects/static/Coin.h"
#include "GameObjects/moving/Player.h"

Coin::Coin(const sf::Texture& texture, std::function<void()> onCollected)
    : StaticObject(texture, GameObjects::Coin), m_isCollected(false), m_onCollected(std::move(onCollected)) {}

void Coin::handleCollision(GameObject& other) {
    other.handleCollision(*this);
}

void Coin::handleCollision(Player& other) {
    // Collect coin on collision.
    if (m_isCollected) return;
    (void)other;
    setDeleted();
    if (m_onCollected) m_onCollected();
    m_isCollected = true;
}
