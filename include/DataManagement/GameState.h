#pragma once

/// \brief Manages the state of the current game session (score, lives, level).
class GameState {
public:
    inline static constexpr int DEFAULT_LEVEL_TIME_SECONDS = 60;

    /// \brief Default constructor.
    GameState();
   
    void setNumberOfLevels(int val);
    void setNumberOfLives(int val);
    void setCurrentLevel(int val);
    void setScore(int val);
    void setTotalLives(int val);
    void setRemainingTime(float val);

    int getNumberOfLevels() const;
    int getNumberOfLives() const;
    int getCurrentLevel() const;
    int getScore() const;
    int getTotalLives() const;
    float getRemainingTime() const;

    /// \brief Adds points to the score.
    /// \param amount The points to add.
    void coinCollected(int amount);
    
    /// \brief Handles player being hit.
    /// \return True if player still has lives, false if game over.
    bool playerHit();

    /// \brief Resets the flag indicating the player is currently being repositioned/respawning.
    void resetRepositioningFlag();

private:
    int m_numberOfLevels = 0;
    int m_numberOfLives = 3;
    int m_currentLevel = 1;
    int m_score = 0;
    int m_totalLives = 3;
    float m_remainingTime = 0;

    bool m_isRepositioning = false;
};
