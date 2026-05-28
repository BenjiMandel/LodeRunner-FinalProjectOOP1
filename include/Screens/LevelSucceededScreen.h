#pragma once

#include "OverlayScreen.h"
#include <functional>

class ResourceManager;

class LevelSucceededScreen : public OverlayScreen {
public:
    explicit LevelSucceededScreen(ResourceManager& resourceManager);

    void setOnContinue(std::function<void()> callback);
    void setOnMenu(std::function<void()> callback);
};