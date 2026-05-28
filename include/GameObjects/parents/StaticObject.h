#pragma once
#include "GameObjects/parents/GameObject.h"

class StaticObject : public GameObject {
public:
    
    StaticObject(const sf::Texture& texture, GameObjects objectType);

    using GameObject::handleCollision;

    /// \brief Try to dig this object. Default does nothing.
    virtual void dig() {}

    void handleCollision(Player& other) override;
    void handleCollision(Enemy& other) override;
    
    /// \brief Pure virtual function for collision with GameObject.
    void handleCollision(GameObject& other) override = 0;
};
