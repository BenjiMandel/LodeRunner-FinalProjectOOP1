#pragma once
#include <list>
#include <memory>
#include <SFML/Audio.hpp>
#include "ResourceManager.h"
#include "../Types/Sounds.h"

/// \brief Manages playback of sound effects.
class SoundManager {
public:
    static SoundManager& instance();

    SoundManager(const SoundManager&) = delete;
    void operator=(const SoundManager&) = delete;

    /// \brief Plays background music.
    /// \param sound The background music sound enum.
    /// \param loop Whether to loop the music.
    void playBackgroundMusic(Sounds sound, bool loop = true);

    /// \brief Stops the background music.
    void stopBackgroundMusic();

    /// \brief Updates manager (cleanup, ducking).
    /// Call this in the game loop.
    void update();

    // Specific sound playing methods
    void playLevelLost();
    void playGameOver();
    void playGotCoin();
    void playLevelComplete();
    void playFinishLevel();
    void playFalling();

    /// \brief Toggle ducking (reduce music volume on sfx).
    void setDuckingEnabled(bool enabled);

private:

    SoundManager();

    /// \brief Plays a specific sound effect.
    /// \param sound The sound enum to play.
    void playSound(Sounds sound);

    /// \brief Reduces background music volume while sound effects play.
    void duckBackgroundMusic();


    std::list<std::unique_ptr<sf::Sound>> m_sounds; ///< List of active sounds.
    std::unique_ptr<sf::Sound> m_backgroundMusic;   ///< Background music instance.
    float m_originalBackgroundVolume = 100.0f;     ///< Saved background volume.
    bool m_duckingEnabled = false;                  ///< Whether ducking is enabled.
};
