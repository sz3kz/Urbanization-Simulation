#pragma once
#include <memory>

// NOLINTBEGIN
struct Dummy
{
    int x;
    Dummy(int x)
      : x(x) {};
};
// NOLINTEND

struct CellOccupant
{
    std::unique_ptr<Dummy> occupant;

    // Transfers ownership from the caller to this struct
    explicit CellOccupant(std::unique_ptr<Dummy> building)
      : occupant(std::move(building))
    {
    }
};