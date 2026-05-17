#include "../../include/CellProbabilities.hpp"
#include "../../include/World.hpp"

CellProbabilities::CellProbabilities()
{
    ProbabilityDefaultPercentages defaults;
    probabilities[ProbabilityType::CREATE_NEW_BUILDING] =
      Probability{ 0, defaults.create_new_building };
}