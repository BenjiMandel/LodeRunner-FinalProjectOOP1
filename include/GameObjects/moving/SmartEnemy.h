#pragma once
#include "GameObjects/moving/Enemy.h"
#include <vector>
#include <queue>

class Board;
class Player;

/// \brief A smart enemy that uses BFS to find the shortest path to the player.
class SmartEnemy : public Enemy {
public:
    /// \brief Constructs a SmartEnemy.
    /// \param texture The texture for the enemy.
    /// \param startPos The starting position.
    /// \param board Reference to the game board for pathfinding.
    SmartEnemy(const sf::Texture& texture, sf::Vector2f startPos, Board& board);

    /// \brief Updates the enemy's position and logic.
    /// \param deltaTime Time elapsed since last frame.
    void move(float deltaTime) override;

private:
    using ParentsTable = std::vector<std::vector<sf::Vector2i>>;

    Board& m_board;
    sf::Vector2f m_direction;

    /// \brief Calculates the next move direction using BFS.
    /// \param player Reference to the player to target.
    /// \return Normalized direction vector for the next step.
    sf::Vector2f getNextMoveBFS(const Player& player) const;

    /// \brief Runs the BFS algorithm to fill the parents table.
    /// \param start Starting grid coordinate.
    /// \param target Target grid coordinate.
    /// \return A table mapping each visited node to its parent.
    const ParentsTable& runBFS(sf::Vector2i start, sf::Vector2i target) const;

    /// \brief Processes a neighbor node during BFS.
    /// \param current The current node.
    /// \param dir The direction to the neighbor.
    /// \param parents The parents table to update.
    /// \param q The BFS queue.
    void handleNeighbor(sf::Vector2i current, sf::Vector2i dir, ParentsTable& parents, std::queue<sf::Vector2i>& q) const;

    /// \brief Backtracks from the target to find the first step of the path.
    /// \param parents The parents table from BFS.
    /// \param start The starting node.
    /// \param target The target node.
    /// \return The direction vector for the first step.
    sf::Vector2f findFirstStep(const ParentsTable& parents, sf::Vector2i start, sf::Vector2i target) const;

    /// \brief Checks if a move between two grid cells is valid.
    /// \param current The current cell.
    /// \param next The target cell.
    /// \param dir The direction of movement.
    /// \return True if the move is valid (no walls, valid climbing, etc.).
    bool isMoveValid(sf::Vector2i current, sf::Vector2i next, sf::Vector2i dir) const;

    /// \brief Adjusts vertical alignment when transitioning to/from ladders.
    /// \param desiredDirection The intended move direction.
    /// \return The modified direction vector to ensure proper alignment.
    sf::Vector2f handleLadderAlignment(sf::Vector2f desiredDirection);
    
    /// \brief Converts grid coordinates to vector index safely.
    /// \param coord The grid coordinate.
    /// \return The converted size_t index.
    static size_t toIndex(int coord);
    
    mutable ParentsTable m_parents;
};