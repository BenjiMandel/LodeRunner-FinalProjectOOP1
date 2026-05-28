#include "Screens/HelpScreen.h"
#include "DataManagement/ResourceManager.h"
#include "DataManagement/StyleManager.h"
#include "Types/Fonts.h"
#include "Utilities/Consts.h"

HelpScreen::HelpScreen(ResourceManager& resourceManager)
    : m_title(resourceManager.getFont(Fonts::HennyPenny), "HELP & INSTRUCTIONS", 60),
      m_subText(resourceManager.getFont(Fonts::Roboto), "Press Esc to Go Back", 20),
      m_backButton(resourceManager.getFont(Fonts::HennyPenny), "BACK", 40)
{
    // Sub-text Setup
    m_subText.setFillColor(StyleManager::instance().getTextColor());
    
    // --- Create Content Sections ---

    // 1. Objective
    setupSection(resourceManager, "OBJECTIVE", 
        "Collect all coins to unlock the next level.\nFinish all levels to complete the game!\nAvoid enemies and don't die!");

    // 2. Rules
    setupSection(resourceManager, "RULES",
        "Ground/Rope: Left/Right | Ladder: Up/Down\n"
        "Digging & Jumping Allowed\n"
        "Esc: Back to Menu\n"
        "Collision / Falling Bottom: Lose Life");

    // 3. Scoring
    setupSection(resourceManager, "SCORING",
        "Coin: 2 x Level # points per coin\n"
        "Finish: 50 x Level # per level");

    // 4. Settings
    setupSection(resourceManager, "SETTINGS",
        "Change Themes: Switch between\n'Mario' and 'Lode Runner' visuals.\n"
        "Audio: Toggle music styles.");
}

void HelpScreen::setupSection(ResourceManager& rm, const std::string& headerText, const std::string& bodyText) {
    sf::Text header(rm.getFont(Fonts::HennyPenny), headerText, 28);
    sf::Text body(rm.getFont(Fonts::Roboto), bodyText, 22);
    
    body.setLineSpacing(1.2f);

    m_sections.push_back({header, body});
}

void HelpScreen::setOnBack(std::function<void()> callback) {
    m_onBack = callback;
}

void HelpScreen::handleInput(sf::Vector2f mousePos) {
    // Back Button Click
    if (m_backButton.getGlobalBounds().contains(mousePos)) {
        if (m_onBack) m_onBack();
    }
}

void HelpScreen::update(float deltaTime) {
    (void)deltaTime; // Unused
    // Check for Escape key to go back
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
        if (m_onBack) m_onBack();
    }
}

void HelpScreen::draw(sf::RenderWindow& window) {
    sf::Vector2f viewSize = window.getView().getSize();
    sf::Vector2f center = window.getView().getCenter();
    auto& styleMgr = StyleManager::instance();

    // 1. Background
    m_background.setSize(viewSize);
    m_background.setOrigin({viewSize.x / 2.0f, viewSize.y / 2.0f});
    m_background.setPosition(center);
    m_background.setFillColor(styleMgr.getMenuBackgroundColor());
    window.draw(m_background);

    // 2. Title
    m_title.setFillColor(styleMgr.getHighlightColor());
    m_title.setOutlineColor(sf::Color::Black);
    m_title.setOutlineThickness(2);
    
    sf::FloatRect tBounds = m_title.getLocalBounds();
    m_title.setOrigin({tBounds.size.x / 2.0f, tBounds.size.y / 2.0f});
    m_title.setPosition({center.x, center.y - viewSize.y * 0.42f});
    window.draw(m_title);

    // 3. Sub-text (Hint)
    m_subText.setFillColor(styleMgr.getTextColor());
    sf::FloatRect sBounds = m_subText.getLocalBounds();
    m_subText.setOrigin({sBounds.size.x / 2.0f, sBounds.size.y / 2.0f});
    m_subText.setPosition({center.x, center.y - viewSize.y * 0.35f});
    window.draw(m_subText);

    // 4. Sections Layout (Grid)
    
    float startY = center.y - viewSize.y * 0.2f;
    float row2Y = center.y + viewSize.y * 0.15f;
    
    // Row 1: Objective, Rules
    // Row 2: Scoring, Settings
    
    // Define columns
    float colSpacing = viewSize.x * 0.25f; // Distance from center
    
    std::vector<sf::Vector2f> positions = {
        {center.x - colSpacing, startY}, // Objective
        {center.x + colSpacing, startY}, // Rules
        {center.x - colSpacing, row2Y},  // Scoring
        {center.x + colSpacing, row2Y}   // Settings
    };

    for (size_t i = 0; i < m_sections.size() && i < positions.size(); ++i) {
        auto& sec = m_sections[i];
        sf::Vector2f pos = positions[i];

        // Header Styling
        sec.header.setFillColor(styleMgr.getHighlightColor());
        sf::FloatRect hBounds = sec.header.getLocalBounds();
        sec.header.setOrigin({hBounds.size.x / 2.0f, hBounds.size.y / 2.0f});
        sec.header.setPosition(pos);

        // Body Styling
        sec.body.setFillColor(styleMgr.getTextColor());
        sf::FloatRect bBounds = sec.body.getLocalBounds();
        sec.body.setOrigin({bBounds.size.x / 2.0f, 0});
        sec.body.setPosition({pos.x, pos.y + 25.0f}); // Below header

        window.draw(sec.header);
        window.draw(sec.body);
    }

    // 5. Back Button
    m_backButton.setFillColor(styleMgr.getTextColor());
    sf::FloatRect btnBounds = m_backButton.getLocalBounds();
    m_backButton.setOrigin({btnBounds.size.x / 2.0f, btnBounds.size.y / 2.0f});
    m_backButton.setPosition({center.x, center.y + viewSize.y * 0.40f});

    // Hover Effect
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    if (m_backButton.getGlobalBounds().contains(mousePos)) {
        m_backButton.setFillColor(styleMgr.getHighlightColor());
        m_backButton.setScale({1.1f, 1.1f});
    } else {
        m_backButton.setScale({1.0f, 1.0f});
    }

    window.draw(m_backButton);
}