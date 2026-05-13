#pragma once
#include "World.hpp"
#include "Coordinates.hpp"
class Simulation
{
	void iterate();
	auto checkCellExists(Coordinates const& coords) -> bool;
	auto checkCellEmpty(Coordinates coords) -> bool;
	auto getCellBuildingTypes(Coordinates coords) -> BuildingTypes;
	void appluProbability(Coordinates Coords);
};
