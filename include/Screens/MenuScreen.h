#pragma once

#include "Screen.h"
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>
#include "Types/Buttons.h"
#include <functional>

class ResourceManager;

/// \brief The main menu screen.
class MenuScreen : public Screen {
public:
    explicit MenuScreen(ResourceManager& resourceManager);

    void setOnStartGame(std::function<void()> callback);
    void setOnExit(std::function<void()> callback);
    void setOnHelp(std::function<void()> callback);
    void setOnSettings(std::function<void()> callback);

    /// \brief Refreshes textures (call after style change).
    void refresh();

    void handleInput(sf::Vector2f mousePos) override;
    void draw(sf::RenderWindow& window) override;

private:
    /// \brief Initializes the button objects.
    void initButtons(ResourceManager& resourceManager);

    std::function<void()> m_onStartGame;
    std::function<void()> m_onExit;
    std::function<void()> m_onHelp;
    std::function<void()> m_onSettings;

    struct MenuButton {
        Buttons type;
        sf::Text text;
    };

    std::vector<MenuButton> m_buttons;
    sf::Text m_title;
    sf::Sprite m_settingsButtonSprite;
};