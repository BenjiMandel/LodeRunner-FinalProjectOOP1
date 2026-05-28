#pragma once
#include <string>

/// \brief Definitions of specific paths for styles.
namespace Resources {
namespace Paths {

namespace Common {
    inline const std::string Ladder = "resources/images/ladder.png";
    inline const std::string Rope = "resources/images/rope.png";
    
    inline const std::string RestartButton = "resources/images/restart.png";
    inline const std::string StartButton = "resources/images/start.png";
    inline const std::string HelpButton = "resources/images/help.png";
    inline const std::string ExitButton = "resources/images/exit.png";
    inline const std::string SettingsButton = "resources/images/settings.png";
    
    inline const std::string FontHennyPenny = "resources/fonts/HennyPenny-Regular.ttf";
    inline const std::string FontRoboto = "resources/fonts/Roboto-Medium.ttf";
}

namespace Mario {
    inline const std::string Player = "resources/images/mario/marioPlayer.png";
    inline const std::string Enemy = "resources/images/mario/marioEnemy.png";
    inline const std::string Ground = "resources/images/mario/marioGround.png";
    inline const std::string Coin = "resources/images/mario/marioCoin.png";
    inline const std::string Wall = "resources/images/mario/marioWall.png";

    inline const std::string SoundLevelComplete = "resources/sounds/mario/marioLevelComplete.mp3";
    inline const std::string SoundGameOver = "resources/sounds/mario/marioGameOVer.mp3";
    inline const std::string SoundCoin = "resources/sounds/mario/marioCoin.mp3";
    inline const std::string SoundLifeLost = "resources/sounds/mario/marioLifeLost.mp3";
    inline const std::string SoundFalling = "resources/sounds/mario/marioFalling.mp3";
    inline const std::string SoundBackground = "resources/sounds/mario/marioBackground.mp3";
    inline const std::string SoundFinishLevel = "resources/sounds/mario/marioLevelComplete.mp3"; 
}

namespace LodeRunner {
    inline const std::string Player = "resources/images/LodeRunner/LRPlayer.png";
    inline const std::string Enemy = "resources/images/LodeRunner/LREnemy.png";
    inline const std::string Ground = "resources/images/LodeRunner/LRGround.png";
    inline const std::string Coin = "resources/images/LodeRunner/LRCoin.png";
    inline const std::string Wall = "resources/images/LodeRunner/LRWall.png";

    inline const std::string SoundLevelComplete = "resources/sounds/LRSounds/LRLevelComplete.mp3";
    inline const std::string SoundGameOver = "resources/sounds/LRSounds/LRGameOVer.mp3";
    inline const std::string SoundCoin = "resources/sounds/LRSounds/LRCoin.mp3";
    inline const std::string SoundLifeLost = "resources/sounds/LRSounds/LRLifeLost.mp3";
    inline const std::string SoundFalling = "resources/sounds/LRSounds/LRFalling.mp3";
    inline const std::string SoundBackground = "resources/sounds/LRSounds/LRBackground.mp3";
    inline const std::string SoundFinishLevel = "resources/sounds/LRSounds/LRLevelComplete.mp3"; 
}

} // namespace Paths
} // namespace Resources
