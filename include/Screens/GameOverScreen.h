#pragma once

#include "OverlayScreen.h"
#include <functional>

class ResourceManager;

class GameOverScreen : public OverlayScreen {
public:
    explicit GameOverScreen(ResourceManager& resourceManager);

    void setOnRestart(std::function<void()> callback);
    void setOnMenu(std::function<void()> callback);
};
