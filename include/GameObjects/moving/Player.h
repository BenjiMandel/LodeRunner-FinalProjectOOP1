#pragma once
#include "GameObjects/parents/MovingObject.h"
#include <functional>

class Enemy;
class Board;

/// \brief Represents the player character controlled by the user.
class Player : public MovingObject {
public:
    /// \brief Constructs the Player.
    /// \param texture The player's texture.
    /// \param startPos The starting position.
    /// \param board Reference to the game board.
    Player(const sf::Texture& texture, sf::Vector2f startPos, Board& board);

    /// \brief Updates the player's position based on input and physics.
    /// \param deltaTime Time elapsed since last frame.
    void move(float deltaTime) override;

    /// \brief Checks if the player is currently dead.
    /// \return True if dead.
    bool isDead() const;

    /// \brief Kills the player, triggering death animation/state.
    void kill();

    /// \brief Resets the player to the starting position and state.
    void resetToStartPosition() override;

    // --- Collision Handling ---
    void handleCollision(GameObject& other) override;
    void handleCollision(Wall& other) override;
    void handleCollision(DiggableFloor& other) override;
    void handleCollision(Ladder& other) override;
    void handleCollision(Rope& other) override;
    void handleCollision(Coin& other) override;
    void handleCollision(Enemy& other) override;

private:
    /// \brief Processes player keyboard input to determine movement.
    /// \param step The movement step size based on speed and deltaTime.
    /// \param canClimb Whether the player is on a ladder or rope and can climb.
    /// \return The movement vector for this frame.
    sf::Vector2f handleInput(float step, bool canClimb);

    bool m_isDead = false;
    float m_deathAnimationTimer = 0.0f;
    bool m_wasFalling = false;
    Board& m_board;
};
