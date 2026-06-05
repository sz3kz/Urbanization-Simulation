#include "Building.hpp"
#include "World.hpp"
#include <iostream>

#include <iosfwd>

auto operator<<(std::ostream& os, const Building& building) -> std::ostream&
{
    ;
    if (building.building_state->getBuildingState() == BuildingState::RUIN)
    {
        os << Emoji::DerelictHouse;
    }
    else if (building.building_state->getBuildingState() == BuildingState::BURNING)
    {
        os << Emoji::Fire;
    }
    else if (building.building_state->getBuildingState() == BuildingState::NORMAL)
    {
        os << building.emoji;
    }
    return os;
}
