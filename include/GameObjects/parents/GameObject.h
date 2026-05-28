#pragma once
#include <SFML/Graphics.hpp>
#include "Types/Buttons.h"
#include "Types/Game_Objects.h"

class Player;
class Enemy;
class Wall;
class Ladder;
class Coin;
class Rope;
class DiggableFloor;
class MovingObject;

/// \brief Abstract base class for all entities in the game world.
class GameObject {
public:
    /// \brief Constructs a GameObject.
    /// \param texture The texture for the sprite.
    /// \param buttonType Optional button type if this object acts as a button.
    /// \param objectType The specific game object type.
    GameObject(const sf::Texture& texture, Buttons buttonType = Buttons::Max, GameObjects objectType = GameObjects::Max);

    virtual ~GameObject() = 0;

    GameObject(const GameObject&) = delete;
    GameObject& operator=(const GameObject&) = delete;

    GameObject(GameObject&&) = default;
    GameObject& operator=(GameObject&&) = default;

    /// \brief Draws the object to the window.
    /// \param window The render target.
    virtual void draw(sf::RenderWindow& window);

    // --- Position & Scale ---
    void setPosition(float x, float y);
    void setPosition(const sf::Vector2f& pos);
    sf::Vector2f getPosition() const;

    void setScale(float x, float y);
    sf::Vector2f getScale() const;

    /// \brief Gets the global bounding box of the object.
    virtual sf::FloatRect getBounds() const;

    /// \brief Checks if a point is within the object's bounds.
    /// \param pos The point to check.
    /// \return True if the point is inside the bounds.
    bool contains(sf::Vector2f pos) const;

    // --- Type Getters/Setters ---
    void setButtonType(Buttons type);
    void setObjectType(GameObjects type);
    Buttons getButtonType() const;
    GameObjects getObjectType() const;

    /// \brief Marks the object for deletion in the next update cycle.
    void setDeleted();

    /// \brief Checks if the object is marked for deletion.
    bool isDeleted() const;

    // --- Collision Dispatch (Visitor Pattern) ---
    virtual void handleCollision(GameObject& other) = 0;
    virtual void handleCollision(MovingObject&) {}
    virtual void handleCollision(Player&) {}
    virtual void handleCollision(Enemy&) {}
    virtual void handleCollision(Wall&) {}
    virtual void handleCollision(Ladder&) {}
    virtual void handleCollision(Coin&) {}
    virtual void handleCollision(Rope&) {}
    virtual void handleCollision(DiggableFloor&) {}

private:
    Buttons m_buttonType;
    GameObjects m_objectType;
    sf::Sprite m_sprite;
    bool m_isDeleted = false;

protected:
    /// \brief Protected getter for sprite access in derived classes.
    sf::Sprite& getSprite();
    
    /// \brief Protected const getter for sprite access in derived classes.
    const sf::Sprite& getSprite() const;
};
