#pragma once
#include "GameObjects/parents/GameObject.h"

/// \brief Abstract base class for objects that can move (Player, Enemies).
class MovingObject : public GameObject {
public:
    /// \brief Constructs a MovingObject.
    /// \param texture The texture.
    /// \param startPos The starting position.
    MovingObject(const sf::Texture& texture, sf::Vector2f startPos);
    
    virtual ~MovingObject() = 0;

    // Prevent copying
    MovingObject(const MovingObject&) = delete;
    MovingObject& operator=(const MovingObject&) = delete;

    // Allow moving
    MovingObject(MovingObject&&) = default;
    MovingObject& operator=(MovingObject&&) = default;

    /// \brief Updates the object's position based on physics (gravity) and logic.
    /// \param deltaTime Time elapsed since last frame.
    virtual void move(float deltaTime);

    /// \brief Moves the object to a specific target position, handling facing direction.
    /// \param targetPos The target world coordinates.
    void moveTo(sf::Vector2f targetPos);

    /// \brief Sets the boundaries of the game world.
    /// \param bounds Vector containing width and height.
    static void setWorldBounds(sf::Vector2f bounds);

    /// \brief Resets temporary physics flags (onGround, etc.) before collision checks.
    void resetPhysicsFlags();

    /// \brief Checks if the object is currently standing on something solid.
    bool isOnGround() const;

    /// \brief Manually sets the on-ground status.
    /// \param onGround True if grounded.
    void setOnGround(bool onGround);

    /// \brief Reverts the object's position to where it was in the previous frame.
    /// Used for resolving collisions with solid obstacles.
    void returnToLastPosition();

    /// \brief Resets the object to its initial spawn position.
    virtual void resetToStartPosition();

    /// \brief Centers the object horizontally on the current tile.
    /// Useful for aligning with ladders or ropes.
    /// \param speedFactor Interpolation factor (0-1) for smooth centering.
    void centerHorizontalOnTile(float speedFactor = 0.3f);

    /// \brief Gets the collision bounding box, potentially adjusted for mechanics (e.g. ladders).
    sf::FloatRect getBounds() const override;

    // --- Collision Handling ---
    void handleCollision(Wall& other) override;
    void handleCollision(DiggableFloor& other) override;
    void handleCollision(Ladder& other) override;
    void handleCollision(Rope& other) override;

protected:
    sf::Vector2f m_startPosition;
    sf::Vector2f m_lastPosition;

    static sf::Vector2f m_worldBounds;

    // Physics state flags
    bool m_isOnGround = false;
    bool m_isOnLadder = false;
    bool m_isOnRope = false;

    /// \brief Generic handler for solid obstacles (Walls, Floors).
    /// \param other The obstacle object.
    void handleObstacle(GameObject& other);

private:
    /// \brief Updates the sprite's scale to face the direction of movement.
    /// \param xDelta The change in X position.
    void setDirection(float xDelta);
};
