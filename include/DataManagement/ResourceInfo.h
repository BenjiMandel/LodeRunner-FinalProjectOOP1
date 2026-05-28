#pragma once
#include <string>
#include <optional>

/// \brief Struct holding information about a resource file.
/// \tparam T The type of the resource key (Enum).
template <typename T>
struct ResourceInfo {
    T type;
    std::string path;
    std::optional<char> symbol;

    /// \brief Constructs a ResourceInfo object.
    /// \param type The enum type of the resource.
    /// \param path File path to the resource.
    /// \param symbol Optional character symbol (for parsing text levels).
    ResourceInfo(T type, std::string path, std::optional<char> symbol = std::nullopt)
        : type(type), path(std::move(path)), symbol(symbol) {}
};
