#pragma once
#include <cstdint>

enum class BuildingType : std::uint8_t
{
    SHOP,
    HOUSE,
    FIRESTATION,
    FACTORY,
	CHURCH,
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
