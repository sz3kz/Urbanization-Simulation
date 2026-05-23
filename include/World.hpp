#pragma once
#include <cstdint>

enum class BuildingType : std::uint8_t
{
    SHOP,
    HOUSE,
    FIRESTATION,
    FACTORY,
    NONE,
};

enum class ProbabilityType : std::uint8_t
{
    CREATE_NEW_BUILDING,
    SET_CURRENT_BUILDING_ON_FIRE,
};

struct ProbabilityDefaultPercentages
{
    double create_new_building{ 0.01 };
};

constexpr unsigned int default_properties_house_radius = 1;

constexpr unsigned int normal_state_initial_time_to_live = 100;
constexpr unsigned int burning_state_initial_time_to_live = 5;
constexpr unsigned int ruin_state_initial_time_to_live = 30;
constexpr unsigned int decay = 20;