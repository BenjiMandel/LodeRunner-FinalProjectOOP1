#pragma once
#include "Screen.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include <functional>

class ResourceManager;

/// \brief Displays the help/instructions screen.
class HelpScreen : public Screen {
public:
    /// \brief Constructs the HelpScreen.
    /// \param resourceManager Reference to resource manager.
    explicit HelpScreen(ResourceManager& resourceManager);

    void draw(sf::RenderWindow& window) override;
    void handleInput(sf::Vector2f mousePos) override;
    void update(float deltaTime) override;

    /// \brief Sets the callback for the back button.
    void setOnBack(std::function<void()> callback);

private:
    struct Section {
        sf::Text header;
        sf::Text body;
    };

    sf::RectangleShape m_background;
    sf::Text m_title;
    sf::Text m_subText; // "Esc to BACK"
    
    // Back button
    sf::Text m_backButton;
    std::function<void()> m_onBack;

    std::vector<Section> m_sections;

    void setupSection(ResourceManager& rm, const std::string& headerText, const std::string& bodyText);
};
