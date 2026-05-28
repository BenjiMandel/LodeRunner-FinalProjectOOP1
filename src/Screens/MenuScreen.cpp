#include "Screens/MenuScreen.h"
#include "Utilities/Consts.h"
#include "DataManagement/ResourceManager.h"
#include "DataManagement/StyleManager.h"
#include "Types/Fonts.h"
#include <iostream>

MenuScreen::MenuScreen(ResourceManager& resourceManager) 
    : m_title(resourceManager.getFont(Fonts::HennyPenny)),
      m_settingsButtonSprite(resourceManager.getMenuButtons()[Buttons::Settings]) {
    initButtons(resourceManager);
}

void MenuScreen::setOnStartGame(std::function<void()> callback) {
    m_onStartGame = callback;
}

void MenuScreen::setOnHelp(std::function<void()> callback) {
    m_onHelp = callback;
}

void MenuScreen::setOnSettings(std::function<void()> callback) {
    m_onSettings = callback;
}

void MenuScreen::setOnExit(std::function<void()> callback) {
    m_onExit = callback;
}

void MenuScreen::initButtons(ResourceManager& resourceManager) {
    sf::Font& font = resourceManager.getFont(Fonts::HennyPenny);

    // Title setup
    m_title.setString("LODE RUNNER");
    m_title.setCharacterSize(120);
    m_title.setFillColor(StyleManager::instance().getHighlightColor());
    m_title.setOutlineColor(sf::Color::Black);
    m_title.setOutlineThickness(4);
    sf::FloatRect titleBounds = m_title.getLocalBounds();
    m_title.setOrigin({titleBounds.position.x + titleBounds.size.x / 2.0f, titleBounds.position.y + titleBounds.size.y / 2.0f});

    // Define the buttons we want
    struct BtnDef {
        Buttons type;
        std::string label;
    };
    std::vector<BtnDef> defs = {
        {Buttons::Start, "Play Game"},
        {Buttons::Help, "Help"},
        {Buttons::Exit, "Exit"}
    };

    for (const auto& def : defs) {
        MenuButton mb{def.type, sf::Text(font)};
        mb.text.setString(def.label);
        mb.text.setCharacterSize(60);
        mb.text.setFillColor(StyleManager::instance().getTextColor());
        mb.text.setOutlineColor(sf::Color::Black);
        mb.text.setOutlineThickness(2);
        
        // Center origin for easier positioning
        sf::FloatRect bounds = mb.text.getLocalBounds();
        mb.text.setOrigin({bounds.position.x + bounds.size.x / 2.0f, bounds.position.y + bounds.size.y / 2.0f});

        m_buttons.push_back(std::move(mb));
    }

    // Settings Button
    // Texture set in constructor.
    // Origin center
    sf::FloatRect sBounds = m_settingsButtonSprite.getLocalBounds();
    m_settingsButtonSprite.setOrigin({sBounds.size.x / 2.0f, sBounds.size.y / 2.0f});
}

void MenuScreen::refresh() {
    m_buttons.clear();
    // Re-init buttons with potentially new styles/textures
    // Use Singleton instance for ResourceManager.
    // Draw Dark Brown Background with border.

    initButtons(ResourceManager::instance());
}

void MenuScreen::handleInput(sf::Vector2f mousePos) {
    // Check settings button
    if (m_settingsButtonSprite.getGlobalBounds().contains(mousePos)) {
        if (m_onSettings) m_onSettings();
        return;
    }

    for (auto& button : m_buttons) {
        if (button.text.getGlobalBounds().contains(mousePos)) {
            if (button.type == Buttons::Start) {
                if (m_onStartGame) m_onStartGame();
                return;
            } else if (button.type == Buttons::Help) {
                if (m_onHelp) m_onHelp();
                return;
            } else if (button.type == Buttons::Exit) {
                if (m_onExit) m_onExit();
                return;
            }
        }
    }
}

void MenuScreen::draw(sf::RenderWindow& window) {
    sf::Vector2f viewSize = window.getView().getSize();
    sf::Vector2f viewCenter = window.getView().getCenter();

    // Draw Dark Brown Background with border (Same style as MenuBar but brown)
    sf::RectangleShape background(viewSize);
    background.setPosition(viewCenter - viewSize / 2.0f);
    background.setFillColor(StyleManager::instance().getMenuBackgroundColor());
    background.setOutlineThickness(-15.0f);
    background.setOutlineColor(StyleManager::instance().getMenuBorderColor());
    window.draw(background);

    // Draw Title
    m_title.setPosition({viewCenter.x, viewCenter.y - 250.0f});
    window.draw(m_title);
    
    // Draw Settings Button - Top Right
    // viewCenter + viewSize/2 is bottom right.
    // viewCenter.x + viewSize.x/2 - padding
    // viewCenter.y - viewSize.y/2 + padding
    float padding = 50.0f;
    m_settingsButtonSprite.setPosition({
        viewCenter.x + viewSize.x / 2.0f - padding - m_settingsButtonSprite.getGlobalBounds().size.x/2,
        viewCenter.y - viewSize.y / 2.0f + padding + m_settingsButtonSprite.getGlobalBounds().size.y/2
    });
    window.draw(m_settingsButtonSprite);

    float startX = viewCenter.x;
    float startY = viewCenter.y; // Centered
    float gap = 110.0f;

    for (auto& button : m_buttons) {
        float posY = 0;

        if (button.type == Buttons::Start) {
            posY = startY;
        } else if (button.type == Buttons::Help) {
            posY = startY + gap;
        } else if (button.type == Buttons::Exit) {
            posY = startY + 2 * gap;
        }
        
        button.text.setPosition({startX, posY});
        
        // Simple hover effect
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if (button.text.getGlobalBounds().contains(mousePos)) {
            button.text.setFillColor(StyleManager::instance().getHighlightColor());
            button.text.setScale({1.1f, 1.1f});
        } else {
            button.text.setFillColor(StyleManager::instance().getTextColor());
            button.text.setScale({1.0f, 1.0f});
        }

        window.draw(button.text);
    }
}