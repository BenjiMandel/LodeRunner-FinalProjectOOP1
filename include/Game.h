#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include "Utilities/Consts.h"
#include "Screens/GameScreen.h"
#include "Screens/MenuScreen.h"
#include "DataManagement/ResourceManager.h"
#include "DataManagement/SoundManager.h"
#include "Screens/HelpScreen.h"
#include "Screens/GameOverScreen.h"
#include "Screens/LevelSucceededScreen.h"
#include "Screens/GameCompleteScreen.h"
#include "Screens/SettingsScreen.h"

// Main Game class that manages the window and screen transitions.
class Game {
public:
    /// \brief Constructs the Game object, initializing window and screens.
    Game();

    /// \brief Runs the main game loop.
    void run();

private:
    /// \brief Handles user input and system events.
    void handleEvents();

    /// \brief Sets up screen transitions and button callbacks.
    void initializeCallbacks();
    
    /// \brief Resets window size and view to default.
    void resetWindowView();
    
    /// \brief Starts background music for gameplay.
    void startGameMusic();
    
    /// \brief Stops background music.
    void stopGameMusic();

    sf::RenderWindow m_window;
    GameScreen m_gameScreen;
    MenuScreen m_menuScreen;
    HelpScreen m_helpScreen;
    GameOverScreen m_gameOverScreen;
    LevelSucceededScreen m_levelSucceededScreen;
    GameCompleteScreen m_gameCompleteScreen;
    SettingsScreen m_settingsScreen;
    // Reference to current screen (cannot be null)
    std::reference_wrapper<Screen> m_currentScreen;
};
