#pragma once
#include <SFML/Graphics/Color.hpp>
#include <map>
#include <string>
#include "../Types/Game_Objects.h"
#include "../Types/Sounds.h"
#include "../Types/Buttons.h"
#include "../Types/Fonts.h"
#include "../Types/StyleType.h"

/// \brief Singleton manager for game styles (colors, asset paths).
class StyleManager {
public:
    /// \brief Gets the singleton instance.
    static StyleManager& instance();

    StyleManager(const StyleManager&) = delete;
    void operator=(const StyleManager&) = delete;

    /// \brief Sets the visual style.
    /// \param style The style to apply.
    void setVisualStyle(StyleType style);

    /// \brief Sets the audio style.
    /// \param style The style to apply.
    void setAudioStyle(StyleType style);

    /// \brief Gets the current visual style.
    StyleType getVisualStyle() const;

    /// \brief Gets the current audio style.
    StyleType getAudioStyle() const;

    // --- Color Getters ---
    sf::Color getMenuBackgroundColor() const;
    sf::Color getMenuBorderColor() const;
    sf::Color getHighlightColor() const;
    sf::Color getSecondaryColor() const;
    sf::Color getTextColor() const;

    // --- Path Getters ---
    const std::string& getTexturePath(GameObjects object) const;
    const std::string& getSoundPath(Sounds sound) const;
    const std::string& getButtonPath(Buttons button) const;
    const std::string& getFontPath(Fonts font) const;

private:
    StyleManager();

    StyleType m_visualStyle;
    StyleType m_audioStyle;

    // Cached configurations
    sf::Color m_menuBackgroundColor;
    sf::Color m_menuBorderColor;
    sf::Color m_highlightColor;
    sf::Color m_secondaryColor;
    sf::Color m_textColor;

    std::map<GameObjects, std::string> m_objectPaths;
    std::map<Sounds, std::string> m_soundPaths;
    std::map<Buttons, std::string> m_buttonPaths;
    std::map<Fonts, std::string> m_fontPaths;

    /// \brief Loads visual configuration for the given style.
    void loadVisuals(StyleType style);

    /// \brief Loads audio configuration for the given style.
    void loadAudio(StyleType style);

    void loadMarioVisuals();
    void loadMarioAudio();
    void loadLodeRunnerVisuals();
    void loadLodeRunnerAudio();
};
