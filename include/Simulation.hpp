#pragma once
#include "Board.hpp"
class Simulation
{
  private:
    unsigned long current_iteration;
    unsigned int random_seed;
    Board<CellOccupant> previous_board;
    Board<CellProbabilities> probabilit_board;
    Board<CellOccupant> next_board;

  public:
    Simulation(unsigned long width, unsigned long height, unsigned int random_seed);
    void iterate();
	auto checkCellExists(Coordinates /*const&*/ coords) -> bool;
	auto checkCellEmpty(Coordinates coords) -> bool;
	auto getCellBuildingTypes(Coordinates coords) -> BuildingTypes;
	void applyProbability(Coordinates Coords);

	protected:
	Coordinates size;	
};
