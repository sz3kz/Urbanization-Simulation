#include "Simulation.hpp"
#include "Coordinates.hpp"
#include "Board.hpp"

/* This should create boards*/
Simulation::Simulation(unsigned long width, unsigned long height, unsigned int random_seed) {}
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