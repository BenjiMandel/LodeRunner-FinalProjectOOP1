#pragma once
#include "GameObjects/moving/Enemy.h"

/// \brief A simple enemy that moves randomly.
class StupidEnemy : public Enemy {
public:
    /// \brief Constructs a StupidEnemy.
    /// \param texture The texture.
    /// \param startPos The starting position.
    StupidEnemy(const sf::Texture& texture, sf::Vector2f startPos);

    /// \brief Updates the enemy's random movement.
    /// \param deltaTime Time elapsed since last frame.
    void move(float deltaTime) override;

private:
    /// \brief Picks a random movement direction.
    /// \param canClimb If true, vertical directions (Up/Down) are valid.
    void chooseRandomDirection(bool canClimb);

    sf::Vector2f m_direction;
    sf::Vector2f m_lastPos;
};
