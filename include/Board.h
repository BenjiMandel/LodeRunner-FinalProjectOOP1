#pragma once
#include <vector>
#include <memory>
#include <functional>
#include <SFML/Graphics.hpp>
#include "DataManagement/ResourceManager.h"
#include "DataManagement/SoundManager.h"

class GameObject;
class StaticObject;
class Player;
class Enemy;
class GameState;

class Board {
public:
    /// \brief Constructs the Board with references to the ResourceManager and GameState.
    /// \param resourceManager Reference to the ResourceManager for loading assets.
    /// \param gameState Reference to the GameState for tracking game progress.
    /// \param soundManager Reference to the SoundManager for playing sounds.
    explicit Board(ResourceManager& resourceManager,SoundManager& soundManager, GameState& gameState);

    /// \brief Destructor for the Board.
    ~Board();

    /// \brief Loads a specific level from the resource manager.
    /// \param levelNum The level number (1-based).
    void loadLevel(int levelNum);

    /// \brief Draws the board and all its entities.
    /// \param window The render window.
    void draw(sf::RenderWindow& window);

    /// \brief Updates the board state (entities, collisions).
    /// \param deltaTime Time elapsed since last frame.
    void update(float deltaTime);

    /// \brief Checks if the board currently has a player.
    /// \return True if player exists.
    bool hasPlayer() const;

    /// \brief Gets a reference to the player.
    /// \return Reference to the player.
    Player& getPlayerRef() const;

    /// \brief Gets the list of active enemies.
    /// \return Reference to the vector of enemies.
    std::vector<std::unique_ptr<Enemy>>& getEnemies();

    /// \brief Gets the list of static objects (walls, ladders, etc.).
    /// \return Reference to the vector of static objects.
    std::vector<std::unique_ptr<StaticObject>>& getStatics();

    /// \brief Gets the character at a specific grid coordinate.
    /// \param x Grid X coordinate.
    /// \param y Grid Y coordinate.
    /// \return The character representing the tile, or null terminator if out of bounds.
    char getCharAt(int x, int y) const;

    /// \brief Gets the width of the board in tiles.
    /// \return Width in tiles.
    float getWidth() const;

    /// \brief Gets the height of the board in tiles.
    /// \return Height in tiles.
    float getHeight() const;

    /// \brief Sets the callback for when a level is completed.
    void setOnLevelComplete(std::function<void()> callback);

    /// \brief Sets the callback for when the game is over.
    void setOnGameOver(std::function<void()> callback);

private:
    /// \brief Clears all entities from the board.
    void clearBoard();
    
    /// \brief Creates and adds a game object based on the board symbol.
    /// \param c The character representing the object type.
    /// \param x The x coordinate in world space.
    /// \param y The y coordinate in world space.
    void handleObjectCreation(char c, float x, float y);

    /// \brief Adds a static tile object to the board.
    /// \param obj The static object to add.
    /// \param x The x coordinate in world space.
    /// \param y The y coordinate in world space.
    void addTile(std::unique_ptr<StaticObject> obj, float x, float y);
    
    /// \brief Creates and adds an enemy at the specified position.
    /// \param x The x coordinate in world space.
    /// \param y The y coordinate in world space.
    void addEnemy(float x, float y);
    
    /// \brief Creates and adds the player at the specified position.
    /// \param x The x coordinate in world space.
    /// \param y The y coordinate in world space.
    void addPlayer(float x, float y);
    
    std::vector<std::string> m_grid;

    /// \brief Called when a coin is collected by the player.
    void onCoinCollected();

    GameState& m_gameState;

    ResourceManager& m_resourceManager;
    SoundManager& m_soundManager;
    std::vector<std::unique_ptr<StaticObject>> m_tiles;
    std::vector<std::unique_ptr<Enemy>> m_enemies;
    std::unique_ptr<Player> m_player;

    float m_boardHeight;
    float m_boardWidth;

    bool m_hasStupidEnemy;

    int m_currentLevelCoins = 0;
    int m_collectedCoins = 0;
    std::function<void()> m_onLevelCompleteCallback;
    std::function<void()> m_onGameOverCallback;
};