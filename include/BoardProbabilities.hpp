#pragma once
#include "Board.hpp"
#include "CellProbabilities.hpp"
#include "World.hpp"

class BoardProbabilities : public Board<CellProbabilities>
{
    using Board<CellProbabilities>::Board;

  public:
    [[nodiscard]]
    auto checkProbabilityTypePercentageIsSetAtCoordinates(Coordinates const& coordinates,
                                                          ProbabilityType probability_type,
                                                          unsigned long current_iteration) const
      -> bool;
    auto getProbabilityTypePercentageAtCoordinates(Coordinates const& coordinates,
                                                   ProbabilityType probability_type) -> double;
    void setProbabilityTypePercentageAtCoordinates(Coordinates const& coordinates,
                                                   ProbabilityType probability_type,
                                                   unsigned long current_iteration,
                                                   double percentage);
    void resetProbabilities();
};