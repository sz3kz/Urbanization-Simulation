#pragma once
#include <cstdint>
#include <map>

enum class BuildingType : std::uint8_t
{
    SHOP,
    HOUSE,
    FIRESTATION,
    FACTORY,
    CHURCH,
};

enum class ProbabilityType : std::uint8_t
{
    CREATE_NEW_HOUSE,
    CREATE_NEW_FIRESTATION,
    CREATE_NEW_SHOP,
    CREATE_NEW_FACTORY,
    CREATE_NEW_CHURCH,
    SET_CURRENT_BUILDING_ON_FIRE,
    RESTORE_TIME_TO_LIVE,
    RESTORE_FROM_RUIN,
};

inline std::map<ProbabilityType, double> probability_default_percentages = {
    { ProbabilityType::CREATE_NEW_HOUSE, 0.001 },
    { ProbabilityType::CREATE_NEW_FIRESTATION, 0.00001 },
    { ProbabilityType::CREATE_NEW_SHOP, 0.00001 },
    { ProbabilityType::CREATE_NEW_FACTORY, 0.00001 },
    { ProbabilityType::CREATE_NEW_CHURCH, 0.00001 },
    { ProbabilityType::SET_CURRENT_BUILDING_ON_FIRE, 0.0001 },
    { ProbabilityType::RESTORE_FROM_RUIN, 0 },
    { ProbabilityType::RESTORE_TIME_TO_LIVE, 0 }
};

constexpr double set_adjacent_building_on_fire = 0.8;

constexpr unsigned int default_properties_house_radius = 2;
constexpr unsigned int default_properties_shop_radius = 4;
constexpr unsigned int default_properties_firestation_radius = 6;
constexpr unsigned int default_properties_factory_radius = 4;
constexpr unsigned int default_properties_church_radius = 4;

constexpr unsigned int normal_state_initial_time_to_live = 3750;
constexpr unsigned int burning_state_initial_time_to_live = 200;
constexpr unsigned int ruin_state_initial_time_to_live = 560;
constexpr unsigned int decay = 20;
