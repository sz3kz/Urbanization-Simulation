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

auto Building::getRadius() const -> unsigned int
{
    return this->radius;
}

auto Building::getBuildingState() const -> BuildingState
{
    return this->building_state->getBuildingState();
}

void Building::setBuildingState(BuildingState const& supplied_building_state) const
{
    this->building_state->setBuildingState(supplied_building_state);
}

auto Building::getTimeToLive() const -> unsigned int
{
    return this->building_state->getTimeToLive();
}

void Building::decay() const
{
    this->building_state->doDecay();
}

void Building::resetTimeToLive() const
{
    this->building_state->resetTimeToLive();
}

void Building::setEmoji(std::string const& supplied_emoji)
{
    this->emoji = supplied_emoji;
}