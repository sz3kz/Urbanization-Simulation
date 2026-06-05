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

    [[nodiscard]]
    auto getBuilding() const -> Building*;

    [[nodiscard]]
    auto checkCellEmpty() const -> bool;

    void transformState();

    friend auto operator<<(std::ostream& os, CellOccupant const& cell_occupant) -> std::ostream&;
};