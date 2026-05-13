#include World.hpp
#include Coordinates.hpp
class Simulation
{
	void iterate();
	bool checkCellExists(Coordinates const& coords);
	bool checkCellEmpty(Coordinates coords);
	BuildingTypes getCellBuildingTypes(Coordinates coords);
	void appluProbability(Coordinates Coords);
	
}
