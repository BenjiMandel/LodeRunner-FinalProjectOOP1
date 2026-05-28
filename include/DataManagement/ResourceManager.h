#pragma once
#include <vector>
#include <functional>
#include <map>
#include <array>
#include "../Utilities/Consts.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../Types/Buttons.h"
#include "../Types/Game_Objects.h"
#include "../Types/Sounds.h"
#include "../Types/Fonts.h"
#include "../Utilities/Resources.h"
#include "ResourceInfo.h"

/// \brief Manages loading and accessing game resources (textures, sounds, levels).
class ResourceManager {
public:
    /// \brief Gets the singleton instance.
    static ResourceManager& instance();

    ResourceManager(const ResourceManager&) = delete;
    void operator=(const ResourceManager&) = delete;

    /// \brief Loads all textures, sounds, and level data from disk.
    void loadData();

    /// \brief Gets the map of button textures.
    /// \return Reference to the map.
    std::map<Buttons, sf::Texture>& getButtons();

    /// \brief Gets the map of menu button textures.
    /// \return Reference to the map.
    std::map<Buttons, sf::Texture>& getMenuButtons();

    /// \brief Gets the map of game object textures.
    /// \return Reference to the map.
    std::map<GameObjects, sf::Texture>& getImages();

    /// \brief Gets the map of sound buffers.
    /// \return Reference to the map.
    std::map<Sounds, sf::SoundBuffer>& getSounds();

    /// \brief Gets a specific button texture.
    /// \param button The button type.
    /// \return Reference to the texture.
    sf::Texture& getButton(Buttons button);

    /// \brief Gets a specific game object texture.
    /// \param image The game object type.
    /// \return Reference to the texture.
    sf::Texture& getImage(GameObjects image);

    /// \brief Gets a specific sound buffer.
    /// \param sound The sound type.
    /// \return The sound buffer.
    sf::SoundBuffer& getSound(Sounds sound);

    /// \brief Gets the help screen texture.
    /// \return Reference to the texture.
    sf::Texture& getHelpScreenTexture();

    /// \brief Gets a specific game font.
    /// \param font The font type.
    /// \return Reference to the font.
    sf::Font& getFont(Fonts font);

    /// \brief Gets the grid data for a specific level.
    /// \param levelNumber The level number (1-based).
    /// \return Vector of strings representing the level grid.
    std::vector<std::string> getLevelData(int levelNumber);

    /// \brief Gets the total number of loaded levels.
    /// \return Count of levels.
    int getNumberOfLevels() const;

private:
    /// \brief Default constructor. Automatically loads data.
    ResourceManager();

    std::map<Buttons, sf::Texture> m_buttonTextures;
    std::map<Buttons, sf::Texture> m_menuButtonTextures;
    std::map<GameObjects, sf::Texture> m_imageTextures;
    std::map<Sounds, sf::SoundBuffer> m_soundBuffers;
    std::map<Fonts, sf::Font> m_fonts;

    sf::Texture m_helpScreenTexture;

    std::vector<std::vector<std::string>> m_levelData;

    /// \brief Helper template to load resources from an array of ResourceInfo.
    /// \param resources The array of resource info.
    /// \param dataMap The map to store loaded resources.
    /// \param pathResolver Optional function to resolve paths dynamically (e.g. from StyleManager).
    template<typename Key, typename Value, std::size_t N>
    void loadResources(const std::array<ResourceInfo<Key>, N>& resources, 
                       std::map<Key, Value>& dataMap,
                       std::function<std::string(Key)> pathResolver = nullptr);

    /// \brief Loads the help screen image.
    /// \param filename Path to the image.
    /// \return True on success.
    bool loadHelpScreen(const std::string& filename);

    /// \brief Loads the game fonts.
    void loadFonts();

    /// \brief Loads level data from a file.
    /// \param filename Path to the level file.
    /// \return True on success.
    bool loadLevelData(const std::string& filename);

    /// \brief Reads a single level grid from the file stream.
    /// \param file The file stream.
    /// \param height The height of the level.
    /// \return Vector of strings.
    std::vector<std::string> readLevelGrid(std::ifstream& file, int height);
};
