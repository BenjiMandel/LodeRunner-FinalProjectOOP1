#include "DataManagement/GameState.h"

GameState::GameState()
    : m_numberOfLevels(0),
    m_numberOfLives(3),
    m_currentLevel(1),
    m_score(0),
    m_totalLives(3),
    m_remainingTime(0),
    m_isRepositioning(false)
{
}


// SET Functions

void GameState::setNumberOfLevels(int val) {
    m_numberOfLevels = val;
}

void GameState::setNumberOfLives(int val) {
    m_numberOfLives = val;
}

void GameState::setCurrentLevel(int val) {
    m_currentLevel = val;
}

void GameState::setScore(int val) {
    m_score = val;
}

void GameState::setTotalLives(int val) {
    m_totalLives = val;
}

// GET Functions

int GameState::getNumberOfLevels() const {
    return m_numberOfLevels;
}

int GameState::getNumberOfLives() const {
    return m_numberOfLives;
}

int GameState::getCurrentLevel() const {
    return m_currentLevel;
}

int GameState::getScore() const {
    return m_score;
}

int GameState::getTotalLives() const {
    return m_totalLives;
}

void GameState::setRemainingTime(float val) {
    m_remainingTime = val;
}

float GameState::getRemainingTime() const {
    return m_remainingTime;
}

void GameState::coinCollected(int amount) {
    m_score += amount;
}

bool GameState::playerHit() {
    if (!m_isRepositioning) {
        if (m_numberOfLives > 0) {
            m_numberOfLives--;
        }
    }

    m_isRepositioning = true;
    return m_numberOfLives > 0;
}


void GameState::resetRepositioningFlag() {
    m_isRepositioning = false;
}
