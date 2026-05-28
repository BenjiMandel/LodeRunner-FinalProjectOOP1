#include "DataManagement/ResourceManager.h"
#include "DataManagement/StyleManager.h"
#include <fstream>
#include <iostream>

ResourceManager& ResourceManager::instance() {
    static ResourceManager _instance;
    return _instance;
}

ResourceManager::ResourceManager() {
    loadData();
}

void ResourceManager::loadData() {
    auto& styleMgr = StyleManager::instance();

    loadResources(Resources::buttonResources, m_buttonTextures, std::function<std::string(Buttons)>([&](Buttons b) {
        return styleMgr.getButtonPath(b);
    }));
    
    loadResources(Resources::imageResources, m_imageTextures, std::function<std::string(GameObjects)>([&](GameObjects obj) {
        return styleMgr.getTexturePath(obj);
    }));

    loadResources(Resources::soundResources, m_soundBuffers, std::function<std::string(Sounds)>([&](Sounds s) {
        return styleMgr.getSoundPath(s);
    }));

    loadResources(Resources::menuButtonResources, m_menuButtonTextures, std::function<std::string(Buttons)>([&](Buttons b) {
        return styleMgr.getButtonPath(b);
    }));

    loadHelpScreen(Resources::helpScreenPath);
    loadFonts(); 
    loadLevelData(Resources::boardFilePath);
}

std::map<Buttons, sf::Texture>& ResourceManager::getButtons() {
    return m_buttonTextures;
}

std::map<Buttons, sf::Texture>& ResourceManager::getMenuButtons() {
    return m_menuButtonTextures;
}

std::map<GameObjects, sf::Texture>& ResourceManager::getImages() {
    return m_imageTextures;
}

std::map<Sounds, sf::SoundBuffer>& ResourceManager::getSounds() {
    return m_soundBuffers;
}

sf::Texture& ResourceManager::getButton(Buttons button) {
    return m_buttonTextures[button];
}

sf::Texture& ResourceManager::getImage(GameObjects image) {
    return m_imageTextures[image];
}

sf::SoundBuffer& ResourceManager::getSound(Sounds sound) {
    return m_soundBuffers[sound];
}

sf::Texture& ResourceManager::getHelpScreenTexture() {
    return m_helpScreenTexture;
}

sf::Font& ResourceManager::getFont(Fonts font) {
    return m_fonts[font];
}

std::vector<std::string> ResourceManager::getLevelData(int levelNumber) {
    int levelIndex = levelNumber - 1;
    if (levelIndex < 0 || levelIndex >= static_cast<int>(m_levelData.size())) {
        return {};
    }
    return m_levelData[static_cast<size_t>(levelIndex)];
}

// PRIVATE

template<typename Key, typename Value, std::size_t N>
void ResourceManager::loadResources(const std::array<ResourceInfo<Key>, N>& resources, 
                                    std::map<Key, Value>& dataMap,
                                    std::function<std::string(Key)> pathResolver) {
    const std::size_t count = resources.size();
    for (std::size_t i = 0; i < count; i++) {
        Value val;
        auto resource = resources[i];
        Key type = resource.type;
        
        std::string path;
        if (pathResolver) {
            path = pathResolver(type);
            // Fallback to resource.path if resolver returns empty
            if (path.empty()) path = resource.path;
        } else {
            path = resource.path;
        }

        if (!val.loadFromFile(path)) {
            std::cerr << "Failed to load resource " << path << std::endl;
        }

        if (type != Key::Max) {
            dataMap[type] = val;
        }
    }
}

bool ResourceManager::loadHelpScreen(const std::string& filename) {
    if (!m_helpScreenTexture.loadFromFile(filename)) {
        std::cerr << "Failed to load help screen image from: " << filename << std::endl;
        return false;
    }
    return true;
}

void ResourceManager::loadFonts() {
    auto& styleMgr = StyleManager::instance();
    for (const auto& res : Resources::fontResources) {
        std::string path = styleMgr.getFontPath(res.type);
        if (path.empty()) path = res.path;

        if (!m_fonts[res.type].openFromFile(path)) {
            std::cerr << "Failed to load font from: " << path << std::endl;
        }
    }
}

bool ResourceManager::loadLevelData(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return false;
    }

    m_levelData.clear();
    int width, height;

    while (file >> width >> height) {
        auto level = readLevelGrid(file, height);
        if (level.size() == static_cast<size_t>(height)) {
            m_levelData.push_back(level);
        }
    }

    return !m_levelData.empty();
}

std::vector<std::string> ResourceManager::readLevelGrid(std::ifstream& file, int height) {
    std::vector<std::string> grid;
    std::string line;
    std::getline(file, line); // Consume newline after height

    while (grid.size() < static_cast<size_t>(height) && std::getline(file, line)) {
        grid.push_back(line);
    }
    return grid;
}

int ResourceManager::getNumberOfLevels() const {
    return static_cast<int>(m_levelData.size());
}