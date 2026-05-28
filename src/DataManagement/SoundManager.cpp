#include "DataManagement/SoundManager.h"

SoundManager& SoundManager::instance() {
    static SoundManager _instance;
    return _instance;
}

SoundManager::SoundManager()
    : m_duckingEnabled(false) {}

void SoundManager::playSound(Sounds sound) {
    auto& buffer = ResourceManager::instance().getSound(sound);

    m_sounds.push_back(std::make_unique<sf::Sound>(buffer));
    m_sounds.back()->play();
}

void SoundManager::playLevelLost() {
    playSound(Sounds::LifeLost);
}

void SoundManager::playGameOver() {
    playSound(Sounds::GameOver);
}

void SoundManager::playGotCoin() {
    playSound(Sounds::GotCoin);
}

void SoundManager::playLevelComplete() {
    playSound(Sounds::LevelComplete);
}

void SoundManager::playFinishLevel() {
    playSound(Sounds::FinishLevel);
}

void SoundManager::playFalling() {
    playSound(Sounds::Falling);
}

void SoundManager::setDuckingEnabled(bool enabled) {
    m_duckingEnabled = enabled;
    if (!m_duckingEnabled && m_backgroundMusic) {
        m_backgroundMusic->setVolume(m_originalBackgroundVolume);
    }
}

void SoundManager::playBackgroundMusic(Sounds sound, bool loop) {
    auto& buffer = ResourceManager::instance().getSound(sound);

    m_backgroundMusic = std::make_unique<sf::Sound>(buffer);
    m_backgroundMusic->setLooping(loop);
    m_backgroundMusic->setVolume(m_originalBackgroundVolume);
    m_backgroundMusic->play();
}

void SoundManager::stopBackgroundMusic() {
    if (m_backgroundMusic) {
        m_backgroundMusic->stop();
    }
}

void SoundManager::update() {
    // Remove sounds that have finished playing
    m_sounds.remove_if([](const std::unique_ptr<sf::Sound> &s) {
        return s->getStatus() == sf::Sound::Status::Stopped;
    });

    duckBackgroundMusic();
}

void SoundManager::duckBackgroundMusic() {
    if (!m_backgroundMusic || m_backgroundMusic->getStatus() != sf::Sound::Status::Playing) return;

    if (!m_duckingEnabled) {
        // Restore volume if ducking disabled
        if (m_backgroundMusic->getVolume() != m_originalBackgroundVolume) {
            m_backgroundMusic->setVolume(m_originalBackgroundVolume);
        }
        return;
    }

    // If sound effects playing, duck music.
    if (!m_sounds.empty()) {
        m_backgroundMusic->setVolume(m_originalBackgroundVolume * 0.3f);
    } else {
        m_backgroundMusic->setVolume(m_originalBackgroundVolume);
    }
}
