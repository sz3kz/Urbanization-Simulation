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
inline constexpr std::string DerelicHouse = "🏚️";
inline constexpr std::string BlueTile = "🟦️";
}

enum class BuildingState : std::uint8_t
{
    BURNING,
    NORMAL,
    RUIN,
};

inline std::map<BuildingState, unsigned int> building_state_initial_time_to_live = {
    { BuildingState::NORMAL, 3700 },
    { BuildingState::BURNING, 200 },
    { BuildingState::RUIN, 560 }
};

constexpr double set_adjacent_building_on_fire = 0.8;

constexpr unsigned int default_properties_house_radius = 2;
constexpr unsigned int default_properties_shop_radius = 4;
constexpr unsigned int default_properties_firestation_radius = 6;
constexpr unsigned int default_properties_factory_radius = 4;
constexpr unsigned int default_properties_church_radius = 4;
