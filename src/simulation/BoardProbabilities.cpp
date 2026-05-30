#include "../../include/BoardProbabilities.hpp"
#include "../../include/CellProbabilities.hpp"
#include "../../include/World.hpp"
#include <iostream>
auto BoardProbabilities::getProbabilityTypePercentageAtCoordinates(
  Coordinates const& coordinates,
  ProbabilityType probability_type) const -> double
{
    unsigned int index = this->calculateIndexFromCoordinates(coordinates);
    return this->contents.at(index).probabilities.at(probability_type).value;
}

auto BoardProbabilities::checkProbabilityTypePercentageIsSetAtCoordinates(
  Coordinates const& coordinates,
  ProbabilityType probability_type,
  unsigned long current_iteration) const -> bool
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
    for (unsigned int i = 0; i < this->contents.size(); i++)
    {
        for (auto const& [probability_type, probability] : this->contents.at(i).probabilities)
        {
            double preserved_iteration = probability.last_updated_at_iteration;
            this->contents.at(i).probabilities[probability_type] = Probability(
              preserved_iteration, probability_default_percentages.at(probability_type));
        }
    }
}