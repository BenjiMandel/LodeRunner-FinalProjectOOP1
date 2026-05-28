#pragma once
#include "GameObjects/parents/StaticObject.h"

class MovingObject;

/// \brief Represents a floor tile that can be dug through by the player.
class DiggableFloor : public StaticObject {
public:
    using StaticObject::handleCollision;

    /// \brief Constructs a DiggableFloor.
    /// \param texture The texture.
    explicit DiggableFloor(const sf::Texture& texture);
    ~DiggableFloor() override = default;

    /// \brief Digs a hole in the floor, making it passable.
    void dig() override;

    /// \brief Checks if the floor is currently a hole.
    /// \return True if it is a hole.
    bool isHole() const;

    void handleCollision(GameObject& other) override;
    void handleCollision(MovingObject& other) override;

private:
    bool m_isHole;
};