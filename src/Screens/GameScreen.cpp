#include "Screens/GameScreen.h"
#include "Utilities/Consts.h"
#include "DataManagement/StyleManager.h"
#include "GameObjects/parents/GameObject.h"
#include "GameObjects/moving/Player.h"
#include "GameObjects/moving/Enemy.h"
#include "GameObjects/parents/StaticObject.h"
#include "GameObjects/parents/MovingObject.h"
#include "GameObjects/static/DiggableFloor.h"
#include "Types/Fonts.h"

GameScreen::GameScreen()
    : m_gameState(),
    m_menuBar(Consts::WINDOW_WIDTH, Consts::MENU_BAR_HEIGHT, m_gameState, ResourceManager::instance().getFont(Fonts::HennyPenny)),
    m_board(ResourceManager::instance(), SoundManager::instance(), m_gameState)
{
    initializeCallbacks();
    m_gameState.setNumberOfLevels(ResourceManager::instance().getNumberOfLevels());
}

void GameScreen::initializeCallbacks() {
    m_board.setOnLevelComplete([this]() {
        if (m_gameState.getCurrentLevel() >= m_gameState.getNumberOfLevels()) {
            SoundManager::instance().playLevelComplete();
            if (m_onGameComplete) m_onGameComplete();
        }
        else {
            SoundManager::instance().playFinishLevel();
            if (m_onLevelComplete) m_onLevelComplete();
        }
    });

    m_board.setOnGameOver([this]() {
        SoundManager::instance().playGameOver();
        if (m_onGameOver) m_onGameOver();
    });
}

void GameScreen::setOnLevelComplete(std::function<void()> callback) { m_onLevelComplete = callback; }
void GameScreen::setOnGameComplete(std::function<void()> callback) { m_onGameComplete = callback; }
void GameScreen::setOnGameOver(std::function<void()> callback) { m_onGameOver = callback; }
void GameScreen::setOnExit(std::function<void()> callback) { m_onExit = callback; }

void GameScreen::resizeWindowToLevel(sf::RenderWindow& window) {
    float boardWidth = static_cast<float>(m_board.getWidth()) * Consts::TILE_SIZE;
    float boardHeight = static_cast<float>(m_board.getHeight()) * Consts::TILE_SIZE;
    window.setSize({ static_cast<unsigned int>(boardWidth),
                     static_cast<unsigned int>(boardHeight + Consts::MENU_BAR_HEIGHT) });
}

void GameScreen::startGame(sf::RenderWindow& window) {
    m_gameState.setCurrentLevel(1);
    m_gameState.setNumberOfLives(3);
    m_gameState.setScore(0);
    m_gameState.setRemainingTime(GameState::DEFAULT_LEVEL_TIME_SECONDS);
    m_board.loadLevel(m_gameState.getCurrentLevel());
    resizeWindowToLevel(window);
}

void GameScreen::drawBackground(sf::RenderWindow& window) {
    sf::Vector2f viewSize = window.getView().getSize();
    sf::RectangleShape background(viewSize);
    background.setFillColor(StyleManager::instance().getMenuBackgroundColor());
    background.setOutlineThickness(-10.0f);
    background.setOutlineColor(StyleManager::instance().getMenuBorderColor());
    window.draw(background);
}

void GameScreen::setupBoardView(sf::RenderWindow& window) {
    sf::Vector2u currentWindowSize = window.getSize();
    float boardW = static_cast<float>(m_board.getWidth()) * Consts::TILE_SIZE;
    float boardH = static_cast<float>(m_board.getHeight()) * Consts::TILE_SIZE;
    sf::View gameView;
    gameView.setSize({ boardW, boardH });
    gameView.setCenter({ boardW / 2.f, boardH / 2.f });
    float viewportY = static_cast<float>(Consts::MENU_BAR_HEIGHT) / static_cast<float>(currentWindowSize.y);
    gameView.setViewport(sf::FloatRect({ 0.f, viewportY }, { 1.f, 1.0f - viewportY }));
    window.setView(gameView);
}

void GameScreen::draw(sf::RenderWindow& window) {
    sf::View fixedView(sf::FloatRect({ 0.f, 0.f }, sf::Vector2f(window.getSize())));
    window.setView(fixedView);
    drawBackground(window);
    m_menuBar.setWidth(window.getView().getSize().x);
    window.draw(m_menuBar);
    setupBoardView(window);
    m_board.draw(window);
    window.setView(fixedView);
}

void GameScreen::update(float deltaTime) {
    float remainingTime = m_gameState.getRemainingTime() - deltaTime;
    if (remainingTime < 0.f) {
        gameOver();
        return;
    }
    m_gameState.setRemainingTime(remainingTime);
    m_board.update(deltaTime);
    handleDigInput();
    handleCollisions();
    handleFalling();
    handleDeathTimer(deltaTime);
    if (m_gameState.getNumberOfLives() <= 0)
        gameOver();
}

void GameScreen::handleDigInput() {
    auto& player = m_board.getPlayerRef();
    float direction = 0.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X))
        direction = 1.f;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z))
        direction = -1.f;
    else
        return;

    sf::Vector2f targetPoint = player.getPosition() + sf::Vector2f(direction * Consts::TILE_SIZE, Consts::TILE_SIZE);
    for (auto& obj : m_board.getStatics()) {
        if (obj->getBounds().contains(targetPoint)) {
            obj->dig();
            return;
        }
    }
}

void GameScreen::nextLevel(sf::RenderWindow& window) {
    if (m_gameState.getCurrentLevel() + 1 <= m_gameState.getNumberOfLevels()) {
        m_gameState.setCurrentLevel(m_gameState.getCurrentLevel() + 1);
        m_gameState.setRemainingTime(GameState::DEFAULT_LEVEL_TIME_SECONDS);
        m_board.loadLevel(m_gameState.getCurrentLevel());
        resizeWindowToLevel(window);
    }
    else  gameOver();
}

void GameScreen::gameOver() {
    SoundManager::instance().playGameOver();
    if (m_onGameOver) m_onGameOver();
}

bool GameScreen::checkCollision(GameObject& a, GameObject& b) {
    if (&a == &b) return false;
    if (a.getBounds().findIntersection(b.getBounds())) {
        a.handleCollision(b);
        return true;
    }
    return false;
}

void GameScreen::handleCollisions() {
    auto& player = m_board.getPlayerRef();
    auto& enemies = m_board.getEnemies();
    auto& statics = m_board.getStatics();

    player.resetPhysicsFlags();
    for (auto& enemy : enemies) enemy->resetPhysicsFlags();

    // Check all static collisions without filtering by type
    for (auto& staticObj : statics) {
        checkCollision(player, *staticObj);
        for (auto& enemy : enemies) 
            checkCollision(*enemy, *staticObj);  
    }
    // Check player-enemy collisions
    for (auto& enemy : enemies) {
        if (!player.isDead() && checkCollision(player, *enemy)) {
            m_deathTimer = 0.0f;
            m_isPlayerDying = true;
            SoundManager::instance().playLevelLost();
            m_gameState.playerHit();
        }
    }
    // Check enemy-enemy collisions
    for (auto& enemy : enemies) {
        for (auto& otherEnemy : enemies) 
            checkCollision(*enemy, *otherEnemy);     
    }
}

void GameScreen::handleDeathTimer(float deltaTime) {
    if (m_isPlayerDying) {
        m_deathTimer += deltaTime;
        if (m_deathTimer >= 0.4f) {
            m_board.getPlayerRef().resetToStartPosition();
            m_gameState.resetRepositioningFlag();
            if (m_gameState.getNumberOfLives() > 0) {
                for (auto& enemy : m_board.getEnemies())
                    enemy->resetToStartPosition();
            }
            m_isPlayerDying = false;
            m_deathTimer = 0.0f;
        }
    }
}

void GameScreen::handleFalling() {
    auto& player = m_board.getPlayerRef();
    auto& enemies = m_board.getEnemies();
    float limit = (m_board.getHeight() + 2) * Consts::TILE_SIZE;
    if (player.getPosition().y > limit && !m_isPlayerDying) {
        m_isPlayerDying = true;
        m_deathTimer = 0.0f;
        player.kill();
        SoundManager::instance().playFalling();
        SoundManager::instance().playLevelLost();
        m_gameState.playerHit();
    }
    for (auto i = enemies.begin(); i != enemies.end(); ) {
        if ((*i)->getPosition().y > limit)
            i = enemies.erase(i);
        else
            i++;
    }
}
