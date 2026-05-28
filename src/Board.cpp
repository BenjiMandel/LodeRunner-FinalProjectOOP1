#include "Board.h"
#include "GameObjects/moving/Player.h"
#include "GameObjects/static/Wall.h"
#include "GameObjects/static/Ladder.h"
#include "GameObjects/static/Coin.h"
#include "GameObjects/static/Rope.h"
#include "GameObjects/static/DiggableFloor.h"
#include "GameObjects/moving/SmartEnemy.h"
#include "GameObjects/moving/StupidEnemy.h"
#include <iostream>
#include "DataManagement/GameState.h"
#include "GameObjects/parents/GameObject.h"
#include "Types/BoardSymbols.h"
#include "Utilities/Helpers.h"

Board::Board(ResourceManager &rm, SoundManager &soundManager, GameState &gameState)
    : m_gameState(gameState),
      m_resourceManager(rm),
      m_soundManager(soundManager),
      m_boardHeight(0),
      m_boardWidth(0),
      m_hasStupidEnemy(false) {
}

Board::~Board() = default;

void Board::setOnLevelComplete(std::function<void()> callback) {
    m_onLevelCompleteCallback = callback;
}

void Board::setOnGameOver(std::function<void()> callback) {
    m_onGameOverCallback = callback;
}

void Board::loadLevel(int levelNum) {
    clearBoard();
    m_currentLevelCoins = 0;
    m_collectedCoins = 0;

    m_grid = m_resourceManager.getLevelData(levelNum);

    if (m_grid.empty()) {
        std::cerr << "Error: Level " << levelNum << " empty!\n";
        return;
    }

    m_boardHeight = static_cast<float>(m_grid.size());
    m_boardWidth = static_cast<float>(m_grid[0].size());

    MovingObject::setWorldBounds({m_boardWidth * Consts::TILE_SIZE, m_boardHeight * Consts::TILE_SIZE});

    for (size_t i = 0; i < m_grid.size(); i++) {
        for (size_t j = 0; j < m_grid[i].size(); j++) {
            float x = static_cast<float>(j) * Consts::TILE_SIZE;
            float y = static_cast<float>(i) * Consts::TILE_SIZE;
            handleObjectCreation(m_grid[i][j], x, y);
        }
    }
}

void Board::handleObjectCreation(char c, float x, float y) {
    auto &rm = m_resourceManager;

    if (c == BoardSymbols::Player) {
        addPlayer(x, y);
    } else if (c == BoardSymbols::Enemy) {
        addEnemy(x, y);
    } else if (c == BoardSymbols::Wall) {
        addTile(std::make_unique<Wall>(rm.getImage(GameObjects::Wall)), x, y);
    } else if (c == BoardSymbols::Ladder) {
        addTile(std::make_unique<Ladder>(rm.getImage(GameObjects::Ladder)), x, y);
    } else if (c == BoardSymbols::Rope) {
        addTile(std::make_unique<Rope>(rm.getImage(GameObjects::Rope)), x, y);
    } else if (c == BoardSymbols::Coin) {
        addTile(std::make_unique<Coin>(rm.getImage(GameObjects::Coin), [this]() { onCoinCollected(); }), x, y);
        m_currentLevelCoins++;
    } else if (c == BoardSymbols::DiggableFloor) {
        addTile(std::make_unique<DiggableFloor>(rm.getImage(GameObjects::DiggableFloor)), x, y);
    }
}

void Board::addTile(std::unique_ptr<StaticObject> obj, float x, float y) {
    obj->setPosition(x, y);
    m_tiles.push_back(std::move(obj));
}

void Board::addPlayer(float x, float y) {
    auto &texture = m_resourceManager.getImage(GameObjects::Player);
    sf::Vector2f startPos = Helpers::getTileCenterPosition(x, y);
    m_player = std::make_unique<Player>(texture, startPos, *this);
}

void Board::addEnemy(float x, float y) {
    auto &texture = m_resourceManager.getImage(GameObjects::Enemy);
    sf::Vector2f startPos = Helpers::getTileCenterPosition(x, y);

    if (!m_hasStupidEnemy) {
        auto enemy = std::make_unique<StupidEnemy>(texture, startPos);
        m_enemies.push_back(std::move(enemy));
        m_hasStupidEnemy = true;
    } else {
        auto enemy = std::make_unique<SmartEnemy>(texture, startPos, *this);
        m_enemies.push_back(std::move(enemy));
    }
}

void Board::draw(sf::RenderWindow &window) {
    for (auto &tile: m_tiles) {
        if (!tile->isDeleted()) {
            tile->draw(window);
        }
    }

    for (auto &enemy: m_enemies) {
        enemy->draw(window);
    }
    if (m_player) {
        m_player->draw(window);
    }
}

void Board::update(float deltaTime) {
    if (m_player)
        m_player->move(deltaTime);

    for (auto &enemy: m_enemies)
        enemy->move(deltaTime);
}

void Board::clearBoard() {
    m_tiles.clear();
    m_enemies.clear();
    m_player.reset();
    m_hasStupidEnemy = false;
}

float Board::getWidth() const {
    return m_boardWidth;
}

float Board::getHeight() const {
    return m_boardHeight;
}

char Board::getCharAt(int x, int y) const {
    if (y < 0 || y >= static_cast<int>(m_grid.size()) || x < 0 || x >= static_cast<int>(m_grid[static_cast<size_t>(y)].size())) {
        return BoardSymbols::OutOfBounds;
    }
    return m_grid[static_cast<size_t>(y)][static_cast<size_t>(x)];
}

bool Board::hasPlayer() const {
    return m_player != nullptr;
}

Player& Board::getPlayerRef() const {
    return *m_player;
}

std::vector<std::unique_ptr<Enemy> > &Board::getEnemies() {
    return m_enemies;
}

std::vector<std::unique_ptr<StaticObject> > &Board::getStatics() {
    return m_tiles;
}

void Board::onCoinCollected() {
    m_soundManager.playGotCoin();
    int coinPoints = 2 * m_gameState.getCurrentLevel();
    m_gameState.coinCollected(coinPoints);

    m_collectedCoins++;

    if (m_collectedCoins >= m_currentLevelCoins) {
        int levelBonus = 50 * m_gameState.getCurrentLevel();
        m_gameState.coinCollected(levelBonus);
        if (m_onLevelCompleteCallback) {
            m_onLevelCompleteCallback();
        }
    }
}