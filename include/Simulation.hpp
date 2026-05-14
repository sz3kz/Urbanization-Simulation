#pragma once
#include "Board.hpp"
#include "Coordinates.hpp"
#include "World.hpp"
class Simulation
{
    unsigned int board_width;
    unsigned int board_height;
    unsigned int current_iteration;
    Board previous_board;
    Board probabilit_board;
    Board next_board;

    Simulation(Coordinates size);
    void iterate();
};
