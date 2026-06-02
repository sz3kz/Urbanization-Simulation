#include "CellOccupant.hpp"

#include "../../include/World.hpp"

auto CellOccupant::release() -> std::unique_ptr<Building>
{
    return std::move(this->occupant);
}

auto operator<<(std::ostream& os, CellOccupant const& cell_occupant) -> std::ostream&
{
    if (cell_occupant.occupant == nullptr)
    {
        os << "🟦";
        return os;
    }
    Building const* building = cell_occupant.getBuilding();

    if (building->getBuildingState() == BuildingState::BURNING)
    {
        os << "🔥";
    }
    else if (building->getBuildingState() == BuildingState::RUIN)
    {
        os << "🏚️";
        // os << "🟫";
    }
    else
    {
        os << building_images[building->getBuildingType()];
    }
    /* remove this if not needed anymore
    else if (building->getBuildingType() == BuildingType::HOUSE)
    {
        os << "🏠";
        // os << "🟩";
    }
    else if (building->getBuildingType() == BuildingType::FIRESTATION)
    {
        os << "🚒";
    }
    else if (building->getBuildingType() == BuildingType::SHOP)
    {
        os << "🏪";
    }
    else if (building->getBuildingType() == BuildingType::FACTORY)
    {
        os << "🏭";
    }
    else if (building->getBuildingType() == BuildingType::CHURCH)
    {
        os << "⛪";
        // os << "🫙";
    }*/
    return os;
}
