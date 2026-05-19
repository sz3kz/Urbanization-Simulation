#include "../../include/BoardProbabilities.hpp"
#include "../../include/CellProbabilities.hpp"
#include "../../include/World.hpp"
#include <iostream>
auto BoardProbabilities::getProbabilityTypePercentageAtCoordinates(Coordinates const& coordinates,
                                                                   ProbabilityType probability_type)
  -> double
{
    unsigned int index = this->calculateIndexFromCoordinates(coordinates);
    return this->contents.at(index).probabilities.at(probability_type).value;
}

auto BoardProbabilities::checkProbabilityTypePercentageIsSetAtCoordinates(
  Coordinates const& coordinates,
  ProbabilityType probability_type,
  unsigned long current_iteration) -> bool
{
    unsigned int index = this->calculateIndexFromCoordinates(coordinates);
    return this->contents.at(index).probabilities.at(probability_type).last_updated_at_iteration ==
           current_iteration;
}

void BoardProbabilities::setProbabilityTypePercentageAtCoordinates(Coordinates const& coordinates,
                                                                   ProbabilityType probability_type,
                                                                   unsigned long current_iteration,
                                                                   double percentage)
{
    unsigned int index = this->calculateIndexFromCoordinates(coordinates);
    this->contents.at(index).probabilities[probability_type] =
      Probability(current_iteration, percentage);
}
void BoardProbabilities::resetProbabilities()
{
    ProbabilityDefaultPercentages defaults;
    for (unsigned int i = 0; i < this->contents.size(); i++)
    {
        double preserved_iteration =
          (this->contents.at(i).probabilities.at(ProbabilityType::CREATE_NEW_BUILDING))
            .last_updated_at_iteration;
        this->contents.at(i).probabilities[ProbabilityType::CREATE_NEW_BUILDING] =
          Probability(preserved_iteration, defaults.create_new_building);
    }
}