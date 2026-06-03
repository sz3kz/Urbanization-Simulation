#pragma once
#include "BoardOccupants.hpp"
#include "BoardProbabilities.hpp"

#include <chrono>
#include <fstream>
#include <random>
#include <string>
class Simulation
{
    std::string filename;
    unsigned long current_iteration{ 0 };
    BoardOccupants previous_board;
    BoardProbabilities probability_board;
    BoardOccupants next_board;
    std::mt19937 generator;

    void incrementIteration();
    static void sleep(std::chrono::milliseconds timespan);
    void recycleBoards();
    void executeProbability();
    void propagateBuildingProbabilities();
    void setEmptyCellBurningProbabilityToZero();
    void decayBuildings();
    void print(std::ofstream& file) const;
    auto rollProbabilityDice(double percentage) -> bool;

  public:
    Simulation(unsigned int width,
               unsigned int height,
               unsigned int random_seed,
               std::string filename)
      : filename(filename)
      , previous_board(width, height)
      , probability_board(width, height)
      , next_board(width, height)
      , generator(random_seed) {};

    [[noreturn]]
    void run();
};
