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
    }
    else
    {
        os << building_images[building->getBuildingType()];
    }
    return os;
}
