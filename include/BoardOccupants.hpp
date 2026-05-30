#pragma once
#include "Board.hpp"
#include "Building.hpp"
#include "CellOccupant.hpp"
#include "World.hpp"
#include <iostream>

class BoardOccupants : public Board<CellOccupant>
{
  public:
    using Board<CellOccupant>::Board;
    auto checkCellEmptyAtCoordinates(Coordinates const& coordinates) -> bool;
    auto releaseOccupantAtCoordinates(Coordinates const& coordinates) -> std::unique_ptr<Building>;
    void acquireOccupantToCoordinates(Coordinates const& coordinates,
                                      std::unique_ptr<Building> building);
    auto getCellBuildingType(Coordinates const& coordinates) -> BuildingType;
    /*auto getCellOccupantAtCoordinates(Coordinates const& coords) -> CellOccupant *;*/
    /*void applyProbability(Coordinates const& coordinates);*/
    friend auto operator<<(std::ostream& os, BoardOccupants const& board) -> std::ostream&;
};