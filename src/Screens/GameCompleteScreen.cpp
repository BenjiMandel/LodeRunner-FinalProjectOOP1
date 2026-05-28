#include "Screens/GameCompleteScreen.h"
#include "DataManagement/ResourceManager.h"
#include "Types/Fonts.h"

GameCompleteScreen::GameCompleteScreen(ResourceManager& resourceManager)
    : OverlayScreen(resourceManager, "CONGRATULATIONS!"),
      m_subtitle(resourceManager.getFont(Fonts::HennyPenny))
{
    // Adjust title position to make room for subtitle?
    // Base class draws title at y-150.
    m_titleOffset = 180.0f;
    
    // Setup Subtitle
    m_subtitle.setString("You beat the game!");
    m_subtitle.setCharacterSize(50);
    m_subtitle.setFillColor(sf::Color::White);
    m_subtitle.setOutlineColor(sf::Color::Black);
    m_subtitle.setOutlineThickness(2);

    sf::FloatRect subBounds = m_subtitle.getLocalBounds();
    m_subtitle.setOrigin({subBounds.position.x + subBounds.size.x / 2.0f, subBounds.position.y + subBounds.size.y / 2.0f});

    addButton(resourceManager, Buttons::Menu, "Return to Menu");
}

void GameCompleteScreen::setOnMenu(std::function<void()> callback) {
    setAction(Buttons::Menu, callback);
}

void GameCompleteScreen::drawExtras(sf::RenderWindow& window) {
    sf::Vector2f center = window.getView().getCenter();
    
    // In original code, Title was at -180 and Subtitle at -80.
    // Base class draws Title at -150 offset.
    
    m_subtitle.setPosition({center.x, center.y - 80.0f});
    window.draw(m_subtitle);
}