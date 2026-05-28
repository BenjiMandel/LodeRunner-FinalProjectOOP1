#include "Screens/OverlayScreen.h"
#include "Utilities/Consts.h"
#include "DataManagement/StyleManager.h"
#include "DataManagement/ResourceManager.h"
#include "Types/Fonts.h"

OverlayScreen::OverlayScreen(ResourceManager& resourceManager, const std::string& titleText)
    : m_title(resourceManager.getFont(Fonts::HennyPenny))
{
    // Setup background (Overlay style)
    sf::Vector2f size(Consts::WINDOW_WIDTH / 1.2f, Consts::WINDOW_HEIGHT / 1.2f);
    m_background.setSize(size);
    m_background.setFillColor(StyleManager::instance().getMenuBackgroundColor());
    m_background.setOutlineThickness(-10.0f);
    m_background.setOutlineColor(StyleManager::instance().getMenuBorderColor());
    m_background.setOrigin(size / 2.0f);

    // Setup Title
    m_title.setString(titleText);
    m_title.setCharacterSize(80);
    m_title.setFillColor(StyleManager::instance().getHighlightColor());
    m_title.setOutlineColor(sf::Color::Black);
    m_title.setOutlineThickness(4);

    sf::FloatRect titleBounds = m_title.getLocalBounds();
    m_title.setOrigin({ titleBounds.position.x + titleBounds.size.x / 2.0f, titleBounds.position.y + titleBounds.size.y / 2.0f });
}

void OverlayScreen::addButton(ResourceManager& rm, Buttons type, const std::string& label) {
    sf::Font& font = rm.getFont(Fonts::HennyPenny);

    sf::Text t(font);
    t.setString(label);
    t.setCharacterSize(60);
    t.setFillColor(StyleManager::instance().getTextColor());
    t.setOutlineColor(sf::Color::Black);
    t.setOutlineThickness(2);

    sf::FloatRect bounds = t.getLocalBounds();
    t.setOrigin({ bounds.position.x + bounds.size.x / 2.0f, bounds.position.y + bounds.size.y / 2.0f });

    Button btn = { type, std::move(t) };
    m_buttons.push_back(std::move(btn));
}

void OverlayScreen::setAction(Buttons button, std::function<void()> callback) {
    m_actions[button] = callback;
}

void OverlayScreen::handleInput(sf::Vector2f mousePos) {
    for (const auto& btn : m_buttons) {
        if (btn.text.getGlobalBounds().contains(mousePos)) {
            auto it = m_actions.find(btn.type);
            if (it != m_actions.end() && it->second) {
                it->second();
            }
        }
    }
}

void OverlayScreen::draw(sf::RenderWindow& window) {
    sf::Vector2f center = window.getView().getCenter();

    // Update Style
    m_background.setFillColor(StyleManager::instance().getMenuBackgroundColor());
    m_background.setOutlineColor(StyleManager::instance().getMenuBorderColor());
    m_title.setFillColor(StyleManager::instance().getHighlightColor());

    // Draw background centered
    m_background.setPosition(center);
    window.draw(m_background);

    // Draw Title
    // Position title slightly above the center
    // We might need to adjust this depending on if there are extras
    m_title.setPosition({ center.x, center.y - m_titleOffset });
    window.draw(m_title);

    drawExtras(window);

    float startY = center.y + m_buttonOffsetY;
    float gap = 90.0f;

    for (size_t i = 0; i < m_buttons.size(); ++i) {
        auto& btn = m_buttons[i];
        btn.text.setPosition({ center.x, startY + static_cast<float>(i) * gap });

        // Hover effect
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if (btn.text.getGlobalBounds().contains(mousePos)) {
            btn.text.setFillColor(StyleManager::instance().getHighlightColor());
            btn.text.setScale({ 1.1f, 1.1f });
        }
        else {
            btn.text.setFillColor(StyleManager::instance().getTextColor());
            btn.text.setScale({ 1.0f, 1.0f });
        }

        window.draw(btn.text);
    }
}
