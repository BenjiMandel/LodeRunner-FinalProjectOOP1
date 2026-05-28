#include "Game.h"
#include "Utilities/Consts.h"

Game::Game()
    : m_window(sf::VideoMode({ static_cast<unsigned int>(Consts::WINDOW_WIDTH), static_cast<unsigned int>(Consts::WINDOW_HEIGHT) }), "LodeRunner"),
      m_gameScreen(),
      m_menuScreen(ResourceManager::instance()),
      m_helpScreen(ResourceManager::instance()),
      m_gameOverScreen(ResourceManager::instance()),
      m_levelSucceededScreen(ResourceManager::instance()),
      m_gameCompleteScreen(ResourceManager::instance()),
      m_settingsScreen(ResourceManager::instance()),
      m_currentScreen(m_menuScreen) {

    m_menuScreen.refresh(); // Ensure initial state is consistent
    m_window.setFramerateLimit(Consts::Application::TARGET_FRAMERATE);

    initializeCallbacks();

    startGameMusic();
}

void Game::initializeCallbacks() {
    // --- Start Button ---
    m_menuScreen.setOnStartGame([this]() {
        m_currentScreen = m_gameScreen;
        m_gameScreen.startGame(m_window);
        startGameMusic();
    });

    // --- Help Button ---
    m_menuScreen.setOnHelp([this]() {
        m_currentScreen = m_helpScreen;
    });

    // --- Settings Button ---
    m_menuScreen.setOnSettings([this]() {
        m_currentScreen = m_settingsScreen;
    });

    // --- Settings Screen Callbacks ---
    m_settingsScreen.setOnBack([this]() {
        m_currentScreen = m_menuScreen;
        m_menuScreen.refresh();
    });

    // --- Help Screen Callbacks ---
    m_helpScreen.setOnBack([this]() {
        m_currentScreen = m_menuScreen;
    });

    // --- Exit Button (from Game to Menu) ---
    m_gameScreen.setOnExit([this]() {
        m_currentScreen = m_menuScreen;
        resetWindowView();
    });

    // --- Level Complete ---
    m_gameScreen.setOnLevelComplete([this]() {
        m_currentScreen = m_levelSucceededScreen;
        m_window.setView(m_window.getDefaultView());
        stopGameMusic();
    });

    // --- Game Complete (All Levels) ---
    m_gameScreen.setOnGameComplete([this]() {
        m_currentScreen = m_gameCompleteScreen;
        m_window.setView(m_window.getDefaultView());
        stopGameMusic();
    });

    // --- Game Over ---
    m_gameScreen.setOnGameOver([this]() {
        m_currentScreen = m_gameOverScreen;
        m_window.setView(m_window.getDefaultView());
        stopGameMusic();
    });

    // --- Game Over Screen Callbacks ---
    m_gameOverScreen.setOnRestart([this]() {
        m_currentScreen = m_gameScreen;
        m_gameScreen.startGame(m_window);
        startGameMusic();
    });

    m_gameOverScreen.setOnMenu([this]() {
        m_currentScreen = m_menuScreen;
        resetWindowView();
        startGameMusic();
    });

    // --- Level Succeeded Screen Callbacks ---
    m_levelSucceededScreen.setOnContinue([this]() {
        m_currentScreen = m_gameScreen;
        m_gameScreen.nextLevel(m_window);
        startGameMusic();
    });

    m_levelSucceededScreen.setOnMenu([this]() {
        m_currentScreen = m_menuScreen;
        resetWindowView();
        startGameMusic();
    });

    // --- Game Complete Screen Callbacks ---
    m_gameCompleteScreen.setOnMenu([this]() {
        m_currentScreen = m_menuScreen;
        resetWindowView();
        startGameMusic();
    });

    // --- Exit Button (from Menu to Desktop) ---
    m_menuScreen.setOnExit([this]() {
        m_window.close();
    });
}

void Game::run() {
    sf::Clock clock;
    while (m_window.isOpen()) {
        const float deltaTime = clock.restart().asSeconds();

        handleEvents();
        
        SoundManager::instance().update();
        m_currentScreen.get().update(deltaTime);

        m_window.clear(sf::Color::Black);
        
        const Screen* current = &m_currentScreen.get();
        if (current == &m_gameOverScreen || 
            current == &m_levelSucceededScreen || 
            current == &m_gameCompleteScreen) {
            m_gameScreen.draw(m_window);
        }

        m_currentScreen.get().draw(m_window);
        m_window.display();
    }
}

void Game::handleEvents() {
    while (const std::optional<sf::Event> event = m_window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            m_window.close();
        }

        // Handle Mouse Input
        if (const auto* mouseEvent = event->getIf<sf::Event::MouseButtonPressed>()) {
            sf::Vector2f mousePos = m_window.mapPixelToCoords(mouseEvent->position);
            m_currentScreen.get().handleInput(mousePos);
        }

        // Handle Keyboard (ESC to return to Menu)
        if (const auto* keyEvent = event->getIf<sf::Event::KeyPressed>()) {
            if (keyEvent->code == sf::Keyboard::Key::Escape) {
                if (&m_currentScreen.get() == &m_gameScreen) {
                    resetWindowView();
                }

                m_currentScreen = m_menuScreen;
            }
        }
    }
}

void Game::resetWindowView() {
    m_window.setSize({ Consts::WINDOW_WIDTH, Consts::WINDOW_HEIGHT });
    m_window.setView(m_window.getDefaultView());
}

void Game::startGameMusic() {
    SoundManager::instance().playBackgroundMusic(Sounds::MarioBackground);
}

void Game::stopGameMusic() {
    SoundManager::instance().stopBackgroundMusic();
}
