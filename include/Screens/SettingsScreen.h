#pragma once
#include "Screen.h"
#include <SFML/Graphics.hpp>
#include <functional>
#include <vector>
#include "../Types/Buttons.h"

enum class StyleType;
class ResourceManager;


/// \brief Screen for configuring game settings (Visual and Audio styles).
class SettingsScreen : public Screen {
public:
    /// \brief Constructs the settings screen.
    /// \param resourceManager Reference to the resource manager for loading assets.
    explicit SettingsScreen(ResourceManager& resourceManager);

    /// \brief Draws the settings UI to the window.
    /// \param window The render window.
    void draw(sf::RenderWindow& window) override;

    /// \brief Handles mouse input for setting options.
    /// \param mousePos The current mouse position.
    void handleInput(sf::Vector2f mousePos) override;

    /// \brief Updates screen logic (unused).
    /// \param deltaTime Time elapsed since last frame.
    void update(float deltaTime) override;

    /// \brief Sets the callback for the back button.
    /// \param callback Function to call when back is pressed.
    void setOnBack(std::function<void()> callback);

private:
    /// \brief Initializes UI elements (texts, buttons).
    /// \param resourceManager Reference to resource manager.
    void initUI(ResourceManager& resourceManager);

    /// \brief Updates the preview sprite based on current style.
    void updatePreview();

    sf::Text m_title;
    sf::Text m_visualLabel;
    sf::Text m_audioLabel;
    
    /// \brief Structure representing a clickable text option.
    struct OptionButton {
        sf::Text text;
        bool isSelected;
        std::function<void()> action;
    };
    std::vector<OptionButton> m_visualOptions;
    std::vector<OptionButton> m_audioOptions;

    sf::Text m_backButton;
    std::function<void()> m_onBack;

    // Textures for options (loaded locally to allow showing both styles simultaneously)
    sf::Texture m_marioPlayerTex;
    sf::Texture m_lrPlayerTex;

    // Structure for Visual Option (Image + Text)
    struct VisualOption {
        sf::Sprite sprite;
        sf::Text label;
        sf::RectangleShape border; // To show selection
        StyleType style;
        std::function<void()> action;
    };
    std::vector<VisualOption> m_visualOptionItems;

    // Structure for Audio Option (Text Button)
    struct AudioOption {
        sf::Text text;
        StyleType style;
        std::function<void()> action;
    };
    std::vector<AudioOption> m_audioOptionItems;

    /// \brief Updates visual styling of selected options.
    void updateSelectionVisuals();
    
    /// \brief Reloads fonts based on current style selection.
    void reloadFonts();
    
    /// \brief Adjusts layout based on window size.
    /// \param viewSize The current view size.
    void updateLayout(sf::Vector2f viewSize);
};
