#pragma once

#include "OverlayScreen.h"
#include <functional>

class ResourceManager;

class GameCompleteScreen : public OverlayScreen {
public:
    explicit GameCompleteScreen(ResourceManager& resourceManager);

    void setOnMenu(std::function<void()> callback);

protected:
    void drawExtras(sf::RenderWindow& window) override;

private:
    sf::Text m_subtitle;
};