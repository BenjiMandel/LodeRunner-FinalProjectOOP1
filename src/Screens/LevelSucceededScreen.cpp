#include "Screens/LevelSucceededScreen.h"
#include "DataManagement/ResourceManager.h"

LevelSucceededScreen::LevelSucceededScreen(ResourceManager& resourceManager)
    : OverlayScreen(resourceManager, "LEVEL COMPLETE")
{
    // Base char size is 80.
    m_title.setCharacterSize(90);
    sf::FloatRect titleBounds = m_title.getLocalBounds();
    m_title.setOrigin({titleBounds.position.x + titleBounds.size.x / 2.0f, titleBounds.position.y + titleBounds.size.y / 2.0f});

    addButton(resourceManager, Buttons::Continue, "Continue");
    addButton(resourceManager, Buttons::Menu, "Menu");
}

void LevelSucceededScreen::setOnContinue(std::function<void()> callback) {
    setAction(Buttons::Continue, callback);
}

void LevelSucceededScreen::setOnMenu(std::function<void()> callback) {
    setAction(Buttons::Menu, callback);
}