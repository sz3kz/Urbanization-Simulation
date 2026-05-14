#include "Simulation.hpp"
#include "Coordinates.hpp"

Simulation::Simulation(Coordinates coords)
{
	size = coords;	
}

void Simulation::iterate()
{

}

bool Simulation::checkCellExists(Coordinates /*const&*/ coords)
{
	if (coords.getX() < size.getX() -1 && coords.getY() < size.getY() -1)
	{
		return true;
	}
	return false;
}



