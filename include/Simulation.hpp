#pragma once
#include "BoardOccupants.hpp"
#include "BoardProbabilities.hpp"
#include <fstream>
#include <random>
class Simulation
{
    unsigned long current_iteration{ 0 };
    unsigned int random_seed;
    BoardOccupants previous_board;
    BoardProbabilities probability_board;
    BoardOccupants next_board;
    std::mt19937 generator;

    void iterate();
    void setEmptyCellBurningProbabilityToZero();
    void decayBuildings();
    void print(std::ofstream& file) const;
    auto rollProbabilityDice(double percentage) -> bool;

  public:
    Simulation(unsigned int width, unsigned int height, unsigned int random_seed)
      : random_seed{ random_seed }
      , previous_board(width, height)
      , probability_board(width, height)
      , next_board(width, height)
      , generator(this->random_seed) {};

    [[noreturn]]
    void run();
};
