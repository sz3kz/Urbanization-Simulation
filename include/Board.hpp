#pragma once
#include "CellOccupant.hpp"
#include "Coordinates.hpp"
class Board
{
	public:
	Board(Coordinates const&);
	auto getCellOccupant(Coordinates coords) -> CellOccupant*;
	protected:
	void GenerateBoard();

	Coordinates size;
	CellOccupant*** board;
};
