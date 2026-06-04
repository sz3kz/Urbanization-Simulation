#include "Building.hpp"
#include "World.hpp"
#include <iostream>

#include <iosfwd>

auto operator<<(std::ostream& os, const Building& building) -> std::ostream&
{
    if (building.state_name == BuildingState::RUIN)
    {
        os << Emoji::DerelicHouse;
    }
    else if (building.state_name == BuildingState::BURNING)
    {
        os << Emoji::Fire;
    }
    else if (building.state_name == BuildingState::NORMAL)
    {
        os << building.emoji;
    }
    return os;
}
