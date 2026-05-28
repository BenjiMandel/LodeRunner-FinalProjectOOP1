#pragma once
#include "GameObjects/parents/StaticObject.h"

class MovingObject;

/// \brief Represents a solid wall that blocks movement.
class Wall : public StaticObject {
public:
    using StaticObject::handleCollision;

    /// \brief Constructs a Wall.
    /// \param texture The texture.
    explicit Wall(const sf::Texture& texture);
    ~Wall() override = default;

    void handleCollision(GameObject& other) override;
    void handleCollision(MovingObject& other) override;
};