#include "../../include/BoardProbabilities.hpp"
#include "../../include/CellProbabilities.hpp"
#include "../../include/World.hpp"
#include <iostream>
auto BoardProbabilities::getProbabilityTypePercentageAtCoordinates(Coordinates const& coordinates,
                                                                   ProbabilityType probability_type)
  -> double
{
    auto const& cell = this->getCellAtCoordinates(coordinates);
    return cell.probabilities.at(probability_type).value;
}

auto BoardProbabilities::checkProbabilityTypePercentageIsSetAtCoordinates(
  Coordinates const& coordinates,
  ProbabilityType probability_type,
  unsigned long current_iteration) const -> bool
{
    auto const& cell = this->getCellAtCoordinates(coordinates);
    return cell.probabilities.at(probability_type).last_updated_at_iteration == current_iteration;
}

void BoardProbabilities::setProbabilityTypePercentageAtCoordinates(Coordinates const& coordinates,
                                                                   ProbabilityType probability_type,
                                                                   unsigned long current_iteration,
                                                                   double percentage)
{
    // unsigned int index = this->calculateIndexFromCoordinates(coordinates);
    auto& cell = this->getCellAtCoordinates(coordinates);
    cell.probabilities.at(probability_type) = Probability(current_iteration, percentage);
}
void BoardProbabilities::resetProbabilities()
{

    for (unsigned int i = 0; i < this->getWidth(); ++i)
    {
        for (unsigned int j = 0; j < this->getHeight(); ++j)
        {
            auto& cell =
              this->getCellAtCoordinates(Coordinates(static_cast<int>(i), static_cast<int>(j)));
            for (auto const& [probability_type, probability] : cell.probabilities)
            {
                auto preserved_iteration = probability.last_updated_at_iteration;
                cell.probabilities[probability_type] = Probability(
                  preserved_iteration, probability_default_percentages[probability_type]);
            }
        }
    }
}