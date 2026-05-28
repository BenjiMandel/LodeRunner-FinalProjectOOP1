#pragma once

#include "Screen.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <functional>
#include <string>
#include "Types/Buttons.h"

class ResourceManager;

class OverlayScreen : public Screen {
public:
    /// \brief Constructs an OverlayScreen.
    /// \param resourceManager Reference to resource manager.
    /// \param titleText Text to display as the title.
    OverlayScreen(ResourceManager& resourceManager, const std::string& titleText);

    void handleInput(sf::Vector2f mousePos) override;
    void draw(sf::RenderWindow& window) override;
    void update(float /*deltaTime*/) override {}

protected:
    /// \brief Adds a button to the screen.
    void addButton(ResourceManager& rm, Buttons type, const std::string& label);

    /// \brief Sets the callback action for a button.
    void setAction(Buttons button, std::function<void()> callback);
    
    // Hook for subclasses to draw additional elements (like subtitles)
    virtual void drawExtras(sf::RenderWindow& /*window*/) {}

    struct Button {
        Buttons type;
        sf::Text text;
    };

    sf::RectangleShape m_background;
    sf::Text m_title;
    float m_titleOffset = 150.0f;
    float m_buttonOffsetY = 20.0f;

    std::vector<Button> m_buttons;
    std::map<Buttons, std::function<void()>> m_actions;

private:
};
