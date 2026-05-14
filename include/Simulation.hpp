#pragma once
#include "World.hpp"
#include "Coordinates.hpp"
class Simulation
{
	public:
	Simulation(Coordinates size);
	void iterate();
	auto checkCellExists(Coordinates /*const&*/ coords) -> bool;
	auto checkCellEmpty(Coordinates coords) -> bool;
	auto getCellBuildingTypes(Coordinates coords) -> BuildingTypes;
	void applyProbability(Coordinates Coords);

	protected:
	Coordinates size;	
};
