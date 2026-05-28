#include "Screens/GameOverScreen.h"
#include "DataManagement/ResourceManager.h"

GameOverScreen::GameOverScreen(ResourceManager& resourceManager) 
    : OverlayScreen(resourceManager, "GAME OVER")
{
    // Override default size if needed (Original was 100, Base is 80)
    m_title.setCharacterSize(100);
    // Re-center origin after size change
    sf::FloatRect titleBounds = m_title.getLocalBounds();
    m_title.setOrigin({titleBounds.position.x + titleBounds.size.x / 2.0f, titleBounds.position.y + titleBounds.size.y / 2.0f});

    addButton(resourceManager, Buttons::Restart, "Restart");
    addButton(resourceManager, Buttons::Menu, "Menu");
}

void GameOverScreen::setOnRestart(std::function<void()> callback) {
    setAction(Buttons::Restart, callback);
}

void GameOverScreen::setOnMenu(std::function<void()> callback) {
    setAction(Buttons::Menu, callback);
}
