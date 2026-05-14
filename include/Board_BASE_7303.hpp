#pragma once
#include "CellOccupant.hpp"
#include "Coordinates.hpp"
class Board
{
	Board();
	 auto getCellOccupant(Coordinates coords) -> CellOccupant*;
};
