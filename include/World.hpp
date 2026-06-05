#pragma once
#include <cstdint>
#include <map>
#include <string>

enum class ArgumentType : std::uint8_t
{
    EXEC_NAME,
    WIDTH,
    HEIGHT,
    SEED,
    OUTPUT_FILENAME,
    ARGS,
};

enum class BuildingType : std::uint8_t
{
    SHOP,
    HOUSE,
    FIRESTATION,
    FACTORY,
    CHURCH,
};

namespace Emoji
{
inline constexpr std::string House = "🏠";
inline constexpr std::string Shop = "🏪";
inline constexpr std::string Church = "⛪";
inline constexpr std::string Factory = "🏭";
inline constexpr std::string FireTruck = "🚒";
inline constexpr std::string Fire = "🔥️";
inline constexpr std::string DerelictHouse = "🏚️";
inline constexpr std::string BlueTile = "🟦️";
}

constexpr double set_adjacent_building_on_fire = 0.8;
