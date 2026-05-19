#include "../../include/CellOccupant.hpp"

auto CellOccupant::release() -> std::unique_ptr<Building>
{
    return std::move(this->occupant);
}

auto operator<<(std::ostream& os, CellOccupant const& cell_occupant) -> std::ostream&
{
    if (cell_occupant.occupant)
    {
        os << "🏠";
    }
    else
    {
        os << "🟦";
    }
    return os;
}