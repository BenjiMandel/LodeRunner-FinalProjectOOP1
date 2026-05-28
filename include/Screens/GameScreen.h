#pragma once
#include "Screen.h"
#include "MenuBar.h"
#include "DataManagement/GameState.h"
#include "Board.h"
#include <functional>
#include <SFML/Graphics.hpp>
#include "DataManagement/SoundManager.h"
class ResourceManager;
class GameObject;

/// \brief The main gameplay screen where the action takes place.
class GameScreen : public Screen {
public:
    GameScreen();

    // --- Callbacks ---
    void setOnExit(std::function<void()> callback);
    void setOnLevelComplete(std::function<void()> callback);
    void setOnGameComplete(std::function<void()> callback);
    void setOnGameOver(std::function<void()> callback);

    /// \brief Initializes and starts a new game session.
    /// \param window The render window to resize/setup.
    void startGame(sf::RenderWindow& window);

    /// \brief Advances to the next level.
    /// \param window The render window.
    void nextLevel(sf::RenderWindow& window);

    void draw(sf::RenderWindow& window) override;
    void update(float deltaTime) override;

    /// \brief Checks for player input to dig holes in the floor.
    void handleDigInput();

private:
    /// \brief Sets up board and level completion callbacks.
    void initializeCallbacks();
    
    /// \brief Draws the game background.
    /// \param window The render window.
    void drawBackground(sf::RenderWindow& window);
    
    /// \brief Configures the camera view to center on the board.
    void setupBoardView(sf::RenderWindow& window);

    /// \brief Resizes the window to fit the current level's dimensions.
    void resizeWindowToLevel(sf::RenderWindow& window);

    /// \brief Triggers the game over state.
    void gameOver();
    
    /// \brief Checks if two game objects are colliding.
    /// \param a First game object.
    /// \param b Second game object.
    /// \return True if objects are colliding.
    bool checkCollision(GameObject& a, GameObject& b);
    
    /// \brief Processes all collision checks between entities.
    void handleCollisions();
    
    /// \brief Updates falling state for player and enemies.
    void handleFalling();
    
    /// \brief Updates the death timer and triggers game over when complete.
    /// \param deltaTime Time elapsed since last frame.
    void handleDeathTimer(float deltaTime);

    std::function<void()> m_onExit;
    std::function<void()> m_onLevelComplete;
    std::function<void()> m_onGameComplete;
    std::function<void()> m_onGameOver;
    GameState m_gameState;
    MenuBar m_menuBar;
    Board m_board;
    bool m_isPlayerDying = false;
    float m_deathTimer = 0.0f;
};
