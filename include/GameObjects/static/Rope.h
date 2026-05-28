#pragma once
#include "GameObjects/parents/StaticObject.h"

class MovingObject;

/// \brief Represents a rope that characters can hang from.
class Rope : public StaticObject {
public:
    using StaticObject::handleCollision;

    /// \brief Constructs a Rope.
    /// \param texture The texture.
    explicit Rope(const sf::Texture& texture);
    ~Rope() override = default;

    void handleCollision(GameObject& other) override;
    void handleCollision(MovingObject& other) override;
};