#pragma once
#include <SFML/Graphics.hpp>

namespace Consts {
    /// \brief Global constants for the game window and layout.
    constexpr int WINDOW_WIDTH = 1280;
    constexpr int WINDOW_HEIGHT = 720;
    constexpr int MENU_BAR_HEIGHT = 80;
    constexpr int GAME_HEIGHT = WINDOW_HEIGHT - MENU_BAR_HEIGHT;

    constexpr float TILE_SIZE = 50.0f;
    
    /// \brief Constants related to collision detection and physics.
    namespace Collision {
        /// \brief Reduces hitbox width when on ladders for tighter collision detection.
        constexpr float LADDER_HITBOX_BUFFER = 5.0f;
        
        /// \brief Tolerance for detecting if an object has landed on the ground.
        constexpr float GROUND_COLLISION_TOLERANCE = 5.0f;
        
        /// \brief Alignment tolerance for grabbing onto ropes.
        constexpr float ROPE_ALIGNMENT_TOLERANCE = 5.0f;
    }
    
    /// \brief Constants for character movement and physics.
    namespace Movement {
        /// \brief Minimum threshold for detecting direction changes to flip sprite.
        constexpr float DIRECTION_CHANGE_THRESHOLD = 0.01f;
        
        /// \brief Distance threshold for centering character on tile (ladders/ropes).
        constexpr float CENTERING_THRESHOLD = 1.0f;
        
        /// \brief Half of TILE_SIZE, used for calculating tile centers.
        constexpr float HALF_TILE_SIZE = TILE_SIZE / 2.0f;
    }
    
    /// \brief Constants specific to player behavior and animations.
    namespace Player {
        /// \brief Duration of the player death animation in seconds.
        constexpr float DEATH_ANIMATION_DURATION = 0.5f;
        
        /// \brief Rotation speed during death animation in degrees per second.
        constexpr float DEATH_ROTATION_SPEED = 1200.0f;
        
        /// \brief Offset for checking tiles under player's feet to prevent edge cases.
        constexpr float TILE_CHECK_OFFSET = 1.0f;
    }
    
    /// \brief Constants for enemy AI behavior.
    namespace Enemy {
        /// \brief Smart enemy pathfinding constants.
        namespace Smart {
            /// \brief Epsilon for comparing floating-point direction values.
            constexpr float DIRECTION_EPSILON = 0.001f;
            
            /// \brief Tolerance for vertical alignment when transitioning on/off ladders.
            constexpr float VERTICAL_ALIGNMENT_TOLERANCE = 2.0f;
        }
        
        /// \brief Stupid enemy random movement constants.
        namespace Stupid {
            /// \brief Threshold for detecting if enemy is stuck (not moving).
            constexpr float STUCK_THRESHOLD = 0.1f;
            
            /// \brief Threshold for direction comparisons in movement logic.
            constexpr float DIRECTION_THRESHOLD = 0.1f;
        }
    }
    
    /// \brief Constants for game application settings.
    namespace Application {
        /// \brief Target frames per second for the game loop.
        constexpr unsigned int TARGET_FRAMERATE = 60;
    }
}