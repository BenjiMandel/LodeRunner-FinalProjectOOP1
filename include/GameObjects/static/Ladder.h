#pragma once
#include "GameObjects/parents/StaticObject.h"

class MovingObject;

/// \brief Represents a ladder that can be climbed.
class Ladder : public StaticObject {
public:
    using StaticObject::handleCollision;

    /// \brief Constructs a Ladder.
    /// \param texture The texture.
    explicit Ladder(const sf::Texture& texture);
    ~Ladder() override = default;

    void handleCollision(GameObject& other) override;
    void handleCollision(MovingObject& other) override;
};