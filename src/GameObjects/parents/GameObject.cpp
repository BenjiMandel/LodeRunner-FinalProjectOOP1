#include "GameObjects/parents/GameObject.h"

GameObject::GameObject(const sf::Texture& texture, Buttons buttonType, GameObjects objectType)
    : m_buttonType(buttonType), m_objectType(objectType), m_sprite(texture) {}

GameObject::~GameObject() = default;

void GameObject::draw(sf::RenderWindow& window) {
    window.draw(m_sprite);
}

void GameObject::setPosition(float x, float y) {
    m_sprite.setPosition({ x, y });
}

void GameObject::setPosition(const sf::Vector2f& pos) {
    m_sprite.setPosition(pos);
}

sf::Vector2f GameObject::getPosition() const {
    return m_sprite.getPosition();
}

void GameObject::setScale(float x, float y) {
    m_sprite.setScale({ x, y });
}

sf::Vector2f GameObject::getScale() const {
    return m_sprite.getScale();
}

sf::FloatRect GameObject::getBounds() const {
    return m_sprite.getGlobalBounds();
}

bool GameObject::contains(sf::Vector2f pos) const {
    return m_sprite.getGlobalBounds().contains(pos);
}

void GameObject::setButtonType(Buttons type) {
    m_buttonType = type;
}

void GameObject::setObjectType(GameObjects type) {
    m_objectType = type;
}

Buttons GameObject::getButtonType() const {
    return m_buttonType;
}

GameObjects GameObject::getObjectType() const {
    return m_objectType;
}

void GameObject::setDeleted() {
    m_isDeleted = true;
}

bool GameObject::isDeleted() const {
    return m_isDeleted;
}

sf::Sprite& GameObject::getSprite() {
    return m_sprite;
}

const sf::Sprite& GameObject::getSprite() const {
    return m_sprite;
}

void GameObject::handleCollision(GameObject& other) {
    other.handleCollision(*this);
}

