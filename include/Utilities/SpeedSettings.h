#pragma once

/// \brief Defines movement speeds for various game entities.
namespace SpeedSettings {
    constexpr float GRAVITY_SPEED = 500.0f;       ///< Speed for falling down.
    constexpr float PLAYER_SPEED = 200.0f;        ///< Speed for player walking.
    constexpr float SMART_ENEMY_SPEED = 170.f;    ///< Speed for smart enemy walking.
    constexpr float STUPID_ENEMY_SPEED = 150.f;   ///< Speed for stupid enemy walking.
}
