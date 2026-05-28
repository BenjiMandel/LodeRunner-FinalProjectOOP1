#include "Utilities/Helpers.h"
#include "Utilities/Consts.h"

namespace Helpers {
    bool isZero(const sf::Vector2f& movement) {
        return movement.x == 0.f && movement.y == 0.f;
    }
    
    sf::Vector2f getTileCenterPosition(float x, float y) {
        return sf::Vector2f(x + Consts::Movement::HALF_TILE_SIZE, y + Consts::Movement::HALF_TILE_SIZE);
    }
    
    size_t toIndex(int coord) {
        return static_cast<size_t>(coord);
    }
}
