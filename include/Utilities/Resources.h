#pragma once
#include <array>
#include <optional>
#include <string>
#include "Types/Game_Objects.h"
#include "Types/Buttons.h"
#include "Types/Sounds.h"
#include "Types/Fonts.h"
#include "DataManagement/ResourceInfo.h"
#include "Utilities/Paths.h"
#include "Types/BoardSymbols.h"

/// \brief Definitions of all resources (images, sounds, levels) used in the game.
namespace Resources {

    /// \brief Resources for game objects.
    inline const std::array<ResourceInfo<GameObjects>, 7> imageResources = {
        {
            {GameObjects::Player, Paths::Mario::Player, BoardSymbols::Player},
            {GameObjects::Enemy, Paths::Mario::Enemy, BoardSymbols::Enemy},
            {GameObjects::DiggableFloor, Paths::Mario::Ground, BoardSymbols::DiggableFloor},
            {GameObjects::Ladder, Paths::Common::Ladder, BoardSymbols::Ladder},
            {GameObjects::Coin, Paths::Mario::Coin, BoardSymbols::Coin},
            {GameObjects::Rope, Paths::Common::Rope, BoardSymbols::Rope},
            {GameObjects::Wall, Paths::Mario::Wall, BoardSymbols::Wall}
        }
    };

    /// \brief Resources for in-game buttons.
    inline const std::array<ResourceInfo<Buttons>, 1> buttonResources = {
        {
            {Buttons::Restart, Paths::Common::RestartButton}
        }
    };

    /// \brief Resources for menu buttons.
    inline const std::array<ResourceInfo<Buttons>, 4> menuButtonResources = {
        {
            {Buttons::Start, Paths::Common::StartButton},
            {Buttons::Help, Paths::Common::HelpButton},
            {Buttons::Exit, Paths::Common::ExitButton},
            {Buttons::Settings, Paths::Common::SettingsButton}
        }
    };

    /// \brief Resources for sounds.
    inline const std::array<ResourceInfo<Sounds>, 7> soundResources = {
        {
            {Sounds::FinishLevel, "resources/sounds/finishLevel.mp3"},
            {Sounds::LevelComplete, Paths::Mario::SoundLevelComplete},
            {Sounds::GameOver, Paths::Mario::SoundGameOver},
            {Sounds::GotCoin, Paths::Mario::SoundCoin},
            {Sounds::LifeLost, Paths::Mario::SoundLifeLost},
            {Sounds::Falling, Paths::Mario::SoundFalling},
            {Sounds::MarioBackground, Paths::Mario::SoundBackground}
        }
    };

    /// \brief Resources for fonts.
    inline const std::array<ResourceInfo<Fonts>, 2> fontResources = {
        {
            {Fonts::HennyPenny, Paths::Common::FontHennyPenny},
            {Fonts::Roboto, Paths::Common::FontRoboto}
        }
    };

    /// \brief Path to the help screen image.
    inline const std::string helpScreenPath = "resources/images/help_screen.png";

    /// \brief Path to the level board file.
    inline const std::string boardFilePath = "resources/board.txt";
} // namespace Resources