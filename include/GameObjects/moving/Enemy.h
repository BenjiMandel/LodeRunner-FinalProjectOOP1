#pragma once
#include "GameObjects/parents/MovingObject.h"

/// \brief Abstract base class for all enemies.
class Enemy : public MovingObject {
public:
    using MovingObject::handleCollision;

    /// \brief Constructs an Enemy.
    /// \param texture The texture.
    /// \param startPos The starting position.
    Enemy(const sf::Texture& texture, sf::Vector2f startPos);

    virtual ~Enemy() = default;

    /// \brief Updates the enemy's AI and movement.
    /// \param deltaTime Time elapsed since last frame.
    virtual void move(float deltaTime) override = 0;

    // --- Collision Handling ---
    void handleCollision(GameObject& other) override;
    void handleCollision(Wall& other) override;
    void handleCollision(DiggableFloor& other) override;
    void handleCollision(Ladder& other) override;
    void handleCollision(Rope& other) override;
    void handleCollision(Player& other) override;
    void handleCollision(Enemy& other) override;
};
