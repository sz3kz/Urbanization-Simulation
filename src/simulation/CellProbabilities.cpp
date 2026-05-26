#include "../../include/CellProbabilities.hpp"
#include "../../include/World.hpp"

CellProbabilities::CellProbabilities()
{
    for (auto const& [probability_type, default_value] : probability_default_percentages)
    {
        probabilities[probability_type] = Probability(0, default_value);
    }
}