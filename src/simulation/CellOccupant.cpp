#include "CellOccupant.hpp"

auto CellOccupant::release() -> std::unique_ptr<Building>
{
    return std::move(this->occupant);
}

auto operator<<(std::ostream& os, CellOccupant const& cell_occupant) -> std::ostream&
{
    if (cell_occupant.occupant)
    {
        os << cell_occupant.occupant->getBuildingImage();
        /*
         TODO When implementing other buildings remove these
         if (cell_occupant.occupant->getBuildingType() == BuildingType::CHURCH)
        {
            os << "⛪️";
        }
        else if (cell_occupant.occupant->getBuildingType() == BuildingType::SHOP)
        {
            os << "🏣️";
        }
        else if (cell_occupant.occupant->getBuildingType() == BuildingType::FACTORY)
        {
            os << "🏭️";
        }
        else if (cell_occupant.occupant->getBuildingType() == BuildingType::FIRESTATION)
        {
            os << "🚒️";
        }*/
    }
    else
    {
        os << "🟦";
    }
    return os;
}
