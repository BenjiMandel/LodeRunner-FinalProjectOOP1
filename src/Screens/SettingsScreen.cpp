#include "Screens/SettingsScreen.h"
#include "DataManagement/ResourceManager.h"
#include "DataManagement/StyleManager.h"
#include "DataManagement/SoundManager.h"
#include "Types/Fonts.h"
#include "Types/Game_Objects.h"
#include "Types/Sounds.h"
#include "Utilities/Paths.h"
#include <iostream>

SettingsScreen::SettingsScreen(ResourceManager& resourceManager) 
    : m_title(resourceManager.getFont(Fonts::HennyPenny)),
      m_visualLabel(resourceManager.getFont(Fonts::Roboto)),
      m_audioLabel(resourceManager.getFont(Fonts::Roboto)),
      m_backButton(resourceManager.getFont(Fonts::HennyPenny))
{
    initUI(resourceManager);
    updateSelectionVisuals();
    // Initial layout with default window size
    updateLayout({1200.0f, 900.0f}); 
}

void SettingsScreen::setOnBack(std::function<void()> callback) {
    m_onBack = callback;
}

void SettingsScreen::initUI(ResourceManager& resourceManager) {
    sf::Font& textFont = resourceManager.getFont(Fonts::Roboto);

    // Load Local Textures for Options
    if (!m_marioPlayerTex.loadFromFile(Resources::Paths::Mario::Player)) {
        std::cerr << "Failed to load Mario preview texture\n";
    }
    if (!m_lrPlayerTex.loadFromFile(Resources::Paths::LodeRunner::Player)) {
        std::cerr << "Failed to load LodeRunner preview texture\n";
    }

    // Title
    m_title.setString("SETTINGS");
    m_title.setCharacterSize(80);
    
    // Labels
    m_visualLabel.setString("Visual Style:");
    m_visualLabel.setCharacterSize(40);
    
    m_audioLabel.setString("Audio Style:");
    m_audioLabel.setCharacterSize(40);

    // Back Button (now Save)
    m_backButton.setString("Save");
    m_backButton.setCharacterSize(50);

    // --- Visual Options Setup ---
    // Mario
    m_visualOptionItems.push_back({
        sf::Sprite(m_marioPlayerTex),
        sf::Text(textFont),
        sf::RectangleShape(),
        StyleType::Mario,
        [&, this]() {
            StyleManager::instance().setVisualStyle(StyleType::Mario);
            ResourceManager::instance().loadData(); 
            this->reloadFonts();
            SoundManager::instance().playBackgroundMusic(Sounds::MarioBackground);
            this->updateSelectionVisuals();
        }
    });
    auto& marioVis = m_visualOptionItems.back();
    marioVis.sprite.setScale({2.0f, 2.0f}); // Make it big
    marioVis.label.setString("Mario");
    marioVis.label.setCharacterSize(30);
    marioVis.border.setFillColor(sf::Color::Transparent);
    marioVis.border.setOutlineThickness(3.0f);

    // LodeRunner
    m_visualOptionItems.push_back({
        sf::Sprite(m_lrPlayerTex),
        sf::Text(textFont),
        sf::RectangleShape(),
        StyleType::LodeRunner,
        [&, this]() {
            StyleManager::instance().setVisualStyle(StyleType::LodeRunner);
            ResourceManager::instance().loadData();
            this->reloadFonts();
            SoundManager::instance().playBackgroundMusic(Sounds::MarioBackground);
            this->updateSelectionVisuals();
        }
    });
    auto& lrVis = m_visualOptionItems.back();
    lrVis.sprite.setScale({2.0f, 2.0f});
    lrVis.label.setString("Lode Runner");
    lrVis.label.setCharacterSize(30);
    lrVis.border.setFillColor(sf::Color::Transparent);
    lrVis.border.setOutlineThickness(3.0f);


    // --- Audio Options Setup ---
    // Mario
    m_audioOptionItems.push_back({
        sf::Text(textFont),
        StyleType::Mario,
        [&, this]() {
            StyleManager::instance().setAudioStyle(StyleType::Mario);
            ResourceManager::instance().loadData();
            this->reloadFonts();
            SoundManager::instance().playBackgroundMusic(Sounds::MarioBackground);
            this->updateSelectionVisuals();
        }
    });
    auto& marioAud = m_audioOptionItems.back();
    marioAud.text.setString("Mario");
    marioAud.text.setCharacterSize(35);

    // LodeRunner
    m_audioOptionItems.push_back({
        sf::Text(textFont),
        StyleType::LodeRunner,
        [&, this]() {
            StyleManager::instance().setAudioStyle(StyleType::LodeRunner);
            ResourceManager::instance().loadData();
            this->reloadFonts();
            SoundManager::instance().playBackgroundMusic(Sounds::MarioBackground);
            this->updateSelectionVisuals();
        }
    });
    auto& lrAud = m_audioOptionItems.back();
    lrAud.text.setString("Lode Runner");
    lrAud.text.setCharacterSize(35);
}

void SettingsScreen::reloadFonts() {
    auto& rm = ResourceManager::instance();
    // Re-bind fonts to prevent stale references after reload
    m_title.setFont(rm.getFont(Fonts::HennyPenny));
    m_visualLabel.setFont(rm.getFont(Fonts::Roboto));
    m_audioLabel.setFont(rm.getFont(Fonts::Roboto));
    m_backButton.setFont(rm.getFont(Fonts::HennyPenny));

    for (auto& item : m_visualOptionItems) {
        item.label.setFont(rm.getFont(Fonts::Roboto));
    }
    for (auto& item : m_audioOptionItems) {
        item.text.setFont(rm.getFont(Fonts::Roboto));
    }
}

void SettingsScreen::updateSelectionVisuals() {
    auto& styleMgr = StyleManager::instance();
    sf::Color highlight = styleMgr.getHighlightColor();
    sf::Color textColor = styleMgr.getTextColor();

    StyleType curVis = styleMgr.getVisualStyle();
    StyleType curAud = styleMgr.getAudioStyle();

    sf::Color borderCol = styleMgr.getMenuBorderColor();

    // Update Visual Options
    for (auto& item : m_visualOptionItems) {
        // Selection Logic
        item.border.setOutlineColor(borderCol); 

        if (item.style == curVis) {
            item.border.setOutlineThickness(5.0f); 
            item.border.setFillColor(sf::Color(highlight.r, highlight.g, highlight.b, 50));
            item.label.setFillColor(highlight);
        } else {
            item.border.setOutlineThickness(2.0f);
            item.border.setFillColor(sf::Color::Transparent);
            item.label.setFillColor(textColor);
        }
        
        // Origin centering
        sf::FloatRect sBounds = item.sprite.getLocalBounds();
        item.sprite.setOrigin({sBounds.size.x / 2.0f, sBounds.size.y / 2.0f});

        sf::FloatRect lBounds = item.label.getLocalBounds();
        item.label.setOrigin({lBounds.size.x / 2.0f, lBounds.size.y / 2.0f});
    }

    // Update Audio Options
    for (auto& item : m_audioOptionItems) {
        if (item.style == curAud) {
            item.text.setFillColor(highlight);
        } else {
            item.text.setFillColor(textColor);
        }
        sf::FloatRect b = item.text.getLocalBounds();
        item.text.setOrigin({b.size.x / 2.0f, b.size.y / 2.0f});
    }
}

void SettingsScreen::updateLayout(sf::Vector2f viewSize) {
    sf::Vector2f viewCenter = viewSize / 2.0f;

    auto centerX = [&](sf::Text& txt, float y) {
        sf::FloatRect bounds = txt.getLocalBounds();
        txt.setOrigin({bounds.position.x + bounds.size.x / 2.0f, bounds.position.y + bounds.size.y / 2.0f});
        txt.setPosition({viewCenter.x, y});
    };

    centerX(m_title, viewCenter.y - 300);
    centerX(m_visualLabel, viewCenter.y - 150);
    
    float visOptY = viewCenter.y - 150 + 130;
    float gapX = 300.0f;
    float boxSize = 150.0f;

    for (size_t i = 0; i < m_visualOptionItems.size(); ++i) {
        auto& item = m_visualOptionItems[i];
        float posX = (i == 0) ? (viewCenter.x - gapX/2) : (viewCenter.x + gapX/2);
        float posY = visOptY;

        float contentWidth = std::max(item.sprite.getGlobalBounds().size.x, item.label.getGlobalBounds().size.x);
        float paddedWidth = std::max(boxSize, contentWidth + 40.0f); 
        
        item.border.setSize({paddedWidth, boxSize + 60}); 
        item.border.setOrigin({paddedWidth / 2.0f, (boxSize + 60) / 2.0f});
        item.border.setPosition({posX, posY + 20}); 
        item.sprite.setPosition({posX, posY - 20}); 
        item.label.setPosition({posX, posY + 60});
    }

    float audioY = visOptY + 180;
    centerX(m_audioLabel, audioY);
    float audioOptY = audioY + 60;

    for (size_t i = 0; i < m_audioOptionItems.size(); ++i) {
        auto& item = m_audioOptionItems[i];
        float posX = (i == 0) ? (viewCenter.x - gapX/2) : (viewCenter.x + gapX/2);
        item.text.setPosition({posX, audioOptY});
    }

    centerX(m_backButton, viewCenter.y + 300);
}

void SettingsScreen::handleInput(sf::Vector2f mousePos) {
    // Layout is updated in draw.
    // Ensure layout is initialized before first draw.

    if (m_backButton.getGlobalBounds().contains(mousePos)) {
        if (m_onBack) m_onBack();
        return;
    }

    for (auto& item : m_visualOptionItems) {
        if (item.border.getGlobalBounds().contains(mousePos)) {
            item.action();
        }
    }

    for (auto& item : m_audioOptionItems) {
        if (item.text.getGlobalBounds().contains(mousePos)) {
            item.action();
        }
    }
}

void SettingsScreen::update(float /*deltaTime*/) {
}

void SettingsScreen::draw(sf::RenderWindow& window) {
    sf::Vector2f viewSize = window.getView().getSize();
    sf::Vector2f viewCenter = window.getView().getCenter();
    auto& styleMgr = StyleManager::instance();

    // Refresh layout every frame to handle dynamic window sizes
    updateLayout(viewSize);

    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    // Background
    sf::RectangleShape background(viewSize);
    background.setPosition(viewCenter - viewSize / 2.0f);
    background.setFillColor(styleMgr.getMenuBackgroundColor());
    window.draw(background);

    // Colors
    sf::Color textColor = styleMgr.getTextColor();
    sf::Color highlight = styleMgr.getHighlightColor();
    sf::Color hoverColor = sf::Color(highlight.r, highlight.g, highlight.b, 150);

    // Title
    m_title.setFillColor(highlight);
    window.draw(m_title);

    // --- Visual Section ---
    m_visualLabel.setFillColor(textColor);
    window.draw(m_visualLabel);

    for (size_t i = 0; i < m_visualOptionItems.size(); ++i) {
        auto& item = m_visualOptionItems[i];
        
        // Hover Effect
        bool isHovered = item.border.getGlobalBounds().contains(mousePos);
        if (isHovered && item.style != styleMgr.getVisualStyle()) {
            item.border.setOutlineColor(highlight);
            item.border.setOutlineThickness(3.0f);
        } else if (item.style != styleMgr.getVisualStyle()) {
             item.border.setOutlineColor(styleMgr.getMenuBorderColor());
             item.border.setOutlineThickness(2.0f);
        } else {
             item.border.setOutlineColor(styleMgr.getMenuBorderColor());
        }

        window.draw(item.border);
        window.draw(item.sprite);
        window.draw(item.label);
    }

    // --- Audio Section ---
    m_audioLabel.setFillColor(textColor);
    window.draw(m_audioLabel);

    for (size_t i = 0; i < m_audioOptionItems.size(); ++i) {
        auto& item = m_audioOptionItems[i];
        
        // Hover Effect
        if (item.text.getGlobalBounds().contains(mousePos) && item.style != styleMgr.getAudioStyle()) {
            item.text.setFillColor(hoverColor);
        } else if (item.style != styleMgr.getAudioStyle()) {
            item.text.setFillColor(textColor);
        } else {
            item.text.setFillColor(highlight);
        }

        window.draw(item.text);
    }

    // Save Button
    if (m_backButton.getGlobalBounds().contains(mousePos)) {
        m_backButton.setFillColor(highlight);
    } else {
        m_backButton.setFillColor(textColor);
    }
    window.draw(m_backButton);
}