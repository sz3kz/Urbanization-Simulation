#include "CellOccupant.hpp"

auto CellOccupant::release() -> std::unique_ptr<Building>
{
    return std::move(this->occupant);
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