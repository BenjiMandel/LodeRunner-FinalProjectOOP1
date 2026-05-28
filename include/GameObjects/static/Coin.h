#pragma once
#include "GameObjects/parents/StaticObject.h"
#include <functional>

class Player;

/// \brief Represents a collectible coin.
class Coin : public StaticObject {
public:
    using StaticObject::handleCollision;

    /// \brief Constructs a Coin.
    /// \param texture The texture.
    /// \param onCollected Callback when coin is collected.
    explicit Coin(const sf::Texture &texture, std::function<void()> onCollected = nullptr);

    ~Coin() override = default;

    void handleCollision(GameObject &other) override;

    void handleCollision(Player &other) override;

private:
    bool m_isCollected;
    std::function<void()> m_onCollected;
};
