#pragma once
#include "Building.hpp"
#include <memory>

struct CellOccupant
{
    std::unique_ptr<Building> occupant;

    /* Default constructor is used by std::vector when initializing BoardOccupants */
    CellOccupant()
      : occupant(nullptr)
    {
    }

    // Transfers ownership from the caller to this struct
    explicit CellOccupant(std::unique_ptr<Building> building)
      : occupant(std::move(building))
    {
    }
    auto release() -> std::unique_ptr<Building>;
    friend auto operator<<(std::ostream& os, CellOccupant const& cell_occupant) -> std::ostream&;
};