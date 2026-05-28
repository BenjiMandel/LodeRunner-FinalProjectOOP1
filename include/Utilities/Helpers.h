#pragma once
#include <SFML/Graphics.hpp>
#include <cstddef>

/// \brief Utility helper functions for common calculations and checks.
namespace Helpers {
    /// \brief Checks if a movement vector is zero.
    /// \param movement The movement vector to check.
    /// \return True if both x and y components are zero.
    bool isZero(const sf::Vector2f& movement);
    
    /// \brief Calculates the center position of a tile given its top-left corner.
    /// \param x The x coordinate of the tile's top-left corner.
    /// \param y The y coordinate of the tile's top-left corner.
    /// \return The center position of the tile as a vector.
    sf::Vector2f getTileCenterPosition(float x, float y);
    
    /// \brief Converts grid coordinates to vector index safely.
    /// \param coord The grid coordinate to convert.
    /// \return The coordinate as a size_t for array indexing.
    size_t toIndex(int coord);
}
