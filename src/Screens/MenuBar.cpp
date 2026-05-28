#include "Screens/MenuBar.h"
#include "Utilities/Consts.h"
#include "DataManagement/StyleManager.h"

// Public

MenuBar::MenuBar(float width, float height, GameState& state, const sf::Font& font)
    : m_background(sf::Vector2f(width, height)), state(state), m_font(font) {
    m_background.setFillColor(StyleManager::instance().getMenuBackgroundColor());
    m_background.setOutlineThickness(-2.0f);
    m_background.setOutlineColor(StyleManager::instance().getMenuBorderColor());
}

void MenuBar::setWidth(float width) {
    sf::Vector2f currentSize = m_background.getSize();
    m_background.setSize(sf::Vector2f(width, currentSize.y));
}

// Private

void MenuBar::drawMenuBarInfo(sf::RenderTarget& target, sf::RenderStates states) const {
    float width = m_background.getSize().x;
    float height = m_background.getSize().y;
    float sectionWidth = width / 4.f;
    float centerY = height / 2.f;

    auto configureAndDraw = [&](std::string label, int value, int sectionIndex) {
        sf::Text text = displayText(label, value, sf::Vector2f(0, 0), m_font);
        
        // Center the origin of the text
        sf::FloatRect bounds = text.getLocalBounds();
        text.setOrigin({bounds.position.x + bounds.size.x / 2.f, bounds.position.y + bounds.size.y / 2.f});
        
        // Calculate position: center of the section
        float centerX = (sectionIndex * sectionWidth) + (sectionWidth / 2.f);
        text.setPosition({centerX, centerY});
        
        target.draw(text, states);
    };

    configureAndDraw("Level", state.getCurrentLevel(), 0);
    configureAndDraw("Coins", state.getScore(), 1);
    configureAndDraw("Lives", state.getNumberOfLives(), 2);
    configureAndDraw("Time", static_cast<int>(state.getRemainingTime()), 3);
}

sf::Text MenuBar::displayText(std::string type, int val, sf::Vector2f pos, const sf::Font& font) const {
    sf::Text text(font, type + ": " + std::to_string(val), 45);
    text.setFillColor(StyleManager::instance().getHighlightColor());
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(1);
    text.setPosition(pos);
    return text;
}

void MenuBar::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Update style dynamically
    m_background.setFillColor(StyleManager::instance().getMenuBackgroundColor());
    m_background.setOutlineColor(StyleManager::instance().getMenuBorderColor());

    target.draw(m_background, states);
    drawMenuBarInfo(target, states);
}
