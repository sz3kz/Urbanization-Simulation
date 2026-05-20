#include "House.hpp"
#include "Coordinates.hpp"
#include "World.hpp"
#include <iostream>
#include <string>

constexpr double another_house_in_the_neighbourhood_new_building_probability_decline = 0.3;
constexpr double house_in_the_neighbourhood_new_building_probability_initial_percentage = 0.5;

auto House::getBuildingType() const -> BuildingType
{
    return BuildingType::HOUSE;
}

auto House::getBuildingImage() const -> std ::string
{
    return "🏠";
}

void House::applyProbabilities(
  std::function<bool(Coordinates)> askCellExistsAtCoordinates,
  std::function<bool(Coordinates)> askCellEmptyAtCoordinates,
  std::function<bool(Coordinates, ProbabilityType)> askProbabilityTypePercentageIsSetAtCoordinates,
  std::function<double(Coordinates, ProbabilityType)> askProbabilityTypePercentageAtCoordinates,
  std::function<void(Coordinates, ProbabilityType, double)>
    setCellPercentageOfProbabilityAtCoordinates)
{
    for (int i = (-1) * static_cast<int>(radius); i <= static_cast<int>(radius); ++i)
    {
        for (int j = (-1) * static_cast<int>(radius); j <= static_cast<int>(radius); ++j)
        {
            bool is_self = (i == 0 && j == 0);
            if (is_self)
            {
                continue;
            }
            bool exists = askCellExistsAtCoordinates(Coordinates(i, j));
            if (!exists)
            {
                continue;
            }
            bool empty = askCellEmptyAtCoordinates(Coordinates(i, j));
            if (empty)
            {
                continue;
            }

            bool is_cell_probability_already_set = askProbabilityTypePercentageIsSetAtCoordinates(
              Coordinates(i, j), ProbabilityType::CREATE_NEW_BUILDING);
            if (is_cell_probability_already_set)
            {
                double current_probability = askProbabilityTypePercentageAtCoordinates(
                  Coordinates(i, j), ProbabilityType::CREATE_NEW_BUILDING);
                double new_probability =
                  current_probability -
                  another_house_in_the_neighbourhood_new_building_probability_decline;
                if (new_probability < 0.0)
                {
                    new_probability = 0.0;
                }
                setCellPercentageOfProbabilityAtCoordinates(
                  Coordinates(i, j), ProbabilityType::CREATE_NEW_BUILDING, new_probability);
            }
            else
            {
                setCellPercentageOfProbabilityAtCoordinates(
                  Coordinates(i, j),
                  ProbabilityType::CREATE_NEW_BUILDING,
                  house_in_the_neighbourhood_new_building_probability_initial_percentage);
            }
        }
    }
}
