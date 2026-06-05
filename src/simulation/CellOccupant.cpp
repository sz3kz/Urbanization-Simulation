#include "CellOccupant.hpp"

auto CellOccupant::release() -> std::unique_ptr<Building>
{
    return std::move(this->occupant);
}

auto CellOccupant::getBuilding() const -> Building*
{
    return occupant.get();
}

auto CellOccupant::checkCellEmpty() const -> bool
{
    return occupant == nullptr;
}

void CellOccupant::transformState()
{
    if (occupant->getBuildingState() == BuildingState::NORMAL ||
        occupant->getBuildingState() == BuildingState::BURNING)
    {
        occupant->setBuildingState(BuildingState::RUIN);
    }
    else if (occupant->getBuildingState() == BuildingState::RUIN)
    {
        release();
    }
}

auto operator<<(std::ostream& os, CellOccupant const& cell_occupant) -> std::ostream&
{
    if (cell_occupant.occupant == nullptr)
    {
        os << Emoji::BlueTile;
    }
    else
    {
        os << *(cell_occupant.occupant);
    }
    return os;
}