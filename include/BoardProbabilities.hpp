#pragma once
#include "Board.hpp"
#include "CellProbabilities.hpp"
#include "World.hpp"

class BoardProbabilities : public Board<CellProbabilities>
{
    using Board<CellProbabilities>::Board;

  public:
    auto checkProbabilityTypePercentageIsSetAtCoordinates(Coordinates const& coordinates,
                                                          ProbabilityType probability_type,
                                                          unsigned long current_iteration) -> bool;
    auto getProbabilityTypePercentageAtCoordinates(Coordinates const& coordinates,
                                                   ProbabilityType probability_type) -> double;
    void setProbabilityTypePercentageAtCoordinates(Coordinates const& coordinates,
                                                   ProbabilityType probability_type,
                                                   unsigned long current_iteration,
                                                   double percentage);
    void resetProbabilities();
};
