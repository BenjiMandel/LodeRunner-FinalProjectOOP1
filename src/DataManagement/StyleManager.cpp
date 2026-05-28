#include "DataManagement/StyleManager.h"
#include "Utilities/Resources.h"
#include "Utilities/Paths.h"

StyleManager& StyleManager::instance() {
    static StyleManager _instance;
    return _instance;
}

StyleManager::StyleManager() {
    setVisualStyle(StyleType::Mario);
    setAudioStyle(StyleType::Mario);
}

void StyleManager::setVisualStyle(StyleType style) {
    m_visualStyle = style;
    loadVisuals(style);
}

void StyleManager::setAudioStyle(StyleType style) {
    m_audioStyle = style;
    loadAudio(style);
}

StyleType StyleManager::getVisualStyle() const {
    return m_visualStyle;
}

StyleType StyleManager::getAudioStyle() const {
    return m_audioStyle;
}

sf::Color StyleManager::getMenuBackgroundColor() const {
    return m_menuBackgroundColor;
}

sf::Color StyleManager::getMenuBorderColor() const {
    return m_menuBorderColor;
}

sf::Color StyleManager::getHighlightColor() const {
    return m_highlightColor;
}

sf::Color StyleManager::getSecondaryColor() const {
    return m_secondaryColor;
}

sf::Color StyleManager::getTextColor() const {
    return m_textColor;
}

const std::string& StyleManager::getTexturePath(GameObjects object) const {
    static const std::string emptyString = "";
    auto it = m_objectPaths.find(object);
    if (it != m_objectPaths.end()) {
        return it->second;
    }
    return emptyString; 
}

const std::string& StyleManager::getSoundPath(Sounds sound) const {
    static const std::string emptyString = "";
    auto it = m_soundPaths.find(sound);
    if (it != m_soundPaths.end()) {
        return it->second;
    }
    return emptyString;
}

const std::string& StyleManager::getButtonPath(Buttons button) const {
    static const std::string emptyString = "";
    auto it = m_buttonPaths.find(button);
    if (it != m_buttonPaths.end()) {
        return it->second;
    }
    return emptyString;
}

const std::string& StyleManager::getFontPath(Fonts font) const {
    static const std::string emptyString = "";
    auto it = m_fontPaths.find(font);
    if (it != m_fontPaths.end()) {
        return it->second;
    }
    return emptyString;
}

void StyleManager::loadVisuals(StyleType style) {
    switch (style) {
        case StyleType::Mario:
            loadMarioVisuals();
            break;
        case StyleType::LodeRunner:
            loadLodeRunnerVisuals();
            break;
    }
}

void StyleManager::loadAudio(StyleType style) {
    switch (style) {
        case StyleType::Mario:
            loadMarioAudio();
            break;
        case StyleType::LodeRunner:
            loadLodeRunnerAudio();
            break;
    }
}

void StyleManager::loadMarioVisuals() {
    // Colors
    m_menuBackgroundColor = sf::Color(92, 148, 252); // Mario Sky Blue
    m_menuBorderColor = sf::Color(255, 255, 255);     // White
    m_highlightColor = sf::Color(255, 204, 0);        // Mario Yellow
    m_secondaryColor = sf::Color(230, 0, 18);         // Mario Red
    m_textColor = sf::Color::White;

    // Images
    m_objectPaths[GameObjects::Player] = Resources::Paths::Mario::Player;
    m_objectPaths[GameObjects::Enemy] = Resources::Paths::Mario::Enemy;
    m_objectPaths[GameObjects::DiggableFloor] = Resources::Paths::Mario::Ground;
    m_objectPaths[GameObjects::Ladder] = Resources::Paths::Common::Ladder;
    m_objectPaths[GameObjects::Coin] = Resources::Paths::Mario::Coin;
    m_objectPaths[GameObjects::Rope] = Resources::Paths::Common::Rope;
    m_objectPaths[GameObjects::Wall] = Resources::Paths::Mario::Wall;

    // Buttons
    m_buttonPaths[Buttons::Restart] = Resources::Paths::Common::RestartButton;
    m_buttonPaths[Buttons::Start] = Resources::Paths::Common::StartButton;
    m_buttonPaths[Buttons::Help] = Resources::Paths::Common::HelpButton;
    m_buttonPaths[Buttons::Exit] = Resources::Paths::Common::ExitButton;
    m_buttonPaths[Buttons::Settings] = Resources::Paths::Common::SettingsButton;

    // Fonts
    m_fontPaths[Fonts::HennyPenny] = Resources::Paths::Common::FontHennyPenny;
    m_fontPaths[Fonts::Roboto] = Resources::Paths::Common::FontRoboto;
}

void StyleManager::loadMarioAudio() {
    m_soundPaths[Sounds::FinishLevel] = Resources::Paths::Mario::SoundFinishLevel;
    m_soundPaths[Sounds::LevelComplete] = Resources::Paths::Mario::SoundLevelComplete;
    m_soundPaths[Sounds::GameOver] = Resources::Paths::Mario::SoundGameOver;
    m_soundPaths[Sounds::GotCoin] = Resources::Paths::Mario::SoundCoin;
    m_soundPaths[Sounds::LifeLost] = Resources::Paths::Mario::SoundLifeLost;
    m_soundPaths[Sounds::Falling] = Resources::Paths::Mario::SoundFalling;
    m_soundPaths[Sounds::MarioBackground] = Resources::Paths::Mario::SoundBackground;
}

void StyleManager::loadLodeRunnerVisuals() {
    // Colors - Classic Lode Runner is often black background, blue/brown/white.
    m_menuBackgroundColor = sf::Color(45, 30, 15); // Deeper Dark Brown
    m_menuBorderColor = sf::Color(80, 50, 25);     // Lighter brown border
    m_highlightColor = sf::Color::Green;              // Classic Terminal Green
    m_secondaryColor = sf::Color::Red;
    m_textColor = sf::Color::White;

    // Images
    m_objectPaths[GameObjects::Player] = Resources::Paths::LodeRunner::Player;
    m_objectPaths[GameObjects::Enemy] = Resources::Paths::LodeRunner::Enemy;
    m_objectPaths[GameObjects::DiggableFloor] = Resources::Paths::LodeRunner::Ground;
    // Reuse general assets where LR specific ones don't exist.
    m_objectPaths[GameObjects::Ladder] = Resources::Paths::Common::Ladder; 
    m_objectPaths[GameObjects::Coin] = Resources::Paths::LodeRunner::Coin;
    m_objectPaths[GameObjects::Rope] = Resources::Paths::Common::Rope;
    m_objectPaths[GameObjects::Wall] = Resources::Paths::LodeRunner::Wall;

    // Buttons
    m_buttonPaths[Buttons::Restart] = Resources::Paths::Common::RestartButton;
    m_buttonPaths[Buttons::Start] = Resources::Paths::Common::StartButton;
    m_buttonPaths[Buttons::Help] = Resources::Paths::Common::HelpButton;
    m_buttonPaths[Buttons::Exit] = Resources::Paths::Common::ExitButton;
    m_buttonPaths[Buttons::Settings] = Resources::Paths::Common::SettingsButton;

    // Fonts
    m_fontPaths[Fonts::HennyPenny] = Resources::Paths::Common::FontHennyPenny;
    m_fontPaths[Fonts::Roboto] = Resources::Paths::Common::FontRoboto;
}

void StyleManager::loadLodeRunnerAudio() {
    m_soundPaths[Sounds::FinishLevel] = Resources::Paths::LodeRunner::SoundFinishLevel;
    m_soundPaths[Sounds::LevelComplete] = Resources::Paths::LodeRunner::SoundLevelComplete;
    m_soundPaths[Sounds::GameOver] = Resources::Paths::LodeRunner::SoundGameOver;
    m_soundPaths[Sounds::GotCoin] = Resources::Paths::LodeRunner::SoundCoin;
    m_soundPaths[Sounds::LifeLost] = Resources::Paths::LodeRunner::SoundLifeLost;
    m_soundPaths[Sounds::Falling] = Resources::Paths::LodeRunner::SoundFalling;
    m_soundPaths[Sounds::MarioBackground] = Resources::Paths::LodeRunner::SoundBackground;
}
