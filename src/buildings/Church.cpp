#include "Church.hpp"
#include "CellProbabilities.hpp"
#include "Coordinates.hpp"
#include "World.hpp"
#include <iostream>

constexpr unsigned long church_probability_multiplier = 100;

auto Church::getBuildingType() const -> BuildingType
{
    return BuildingType::CHURCH;
}

void Church::applyProbabilities(
  [[maybe_unused]] std::function<bool(Coordinates)> askCellExistsAtCoordinates,
  [[maybe_unused]] std::function<bool(Coordinates)> askCellEmptyAtCoordinates,
  [[maybe_unused]] std::function<bool(Coordinates, ProbabilityType)>
    askProbabilityTypePercentageIsSetAtCoordinates,
  [[maybe_unused]] std::function<double(Coordinates, ProbabilityType)>
    askProbabilityTypePercentageAtCoordinates,
  [[maybe_unused]] std::function<void(Coordinates, ProbabilityType, double)>
    setCellPercentageOfProbabilityAtCoordinates,
  [[maybe_unused]] std::function<bool(Coordinates, std::string)> askBuildingAtCoordinatesIsInState)
{
    for (int i = (-1) * static_cast<int>(radius); i <= static_cast<int>(radius); ++i)
    {
        for (int j = (-1) * static_cast<int>(radius); j <= static_cast<int>(radius); ++j)
        {
            Coordinates neighbour_position(i, j);
            Coordinates source_position(0, 0);
            if (neighbour_position == source_position)
            {
                setCellPercentageOfProbabilityAtCoordinates(
                  neighbour_position, ProbabilityType::CREATE_NEW_HOUSE, 0.0);
                setCellPercentageOfProbabilityAtCoordinates(
                  neighbour_position, ProbabilityType::CREATE_NEW_FIRESTATION, 0.0);
                setCellPercentageOfProbabilityAtCoordinates(
                  neighbour_position, ProbabilityType::CREATE_NEW_SHOP, 0.0);
                setCellPercentageOfProbabilityAtCoordinates(
                  neighbour_position, ProbabilityType::CREATE_NEW_FACTORY, 0.0);
                setCellPercentageOfProbabilityAtCoordinates(
                  neighbour_position, ProbabilityType::CREATE_NEW_CHURCH, 0.0);
                continue;
            }

            bool neighbour_exists = askCellExistsAtCoordinates(neighbour_position);
            if (!neighbour_exists)
            {
                continue;
            }

            bool neighbour_is_empty = askCellEmptyAtCoordinates(neighbour_position);
            if (neighbour_is_empty)
            {
                setCellPercentageOfProbabilityAtCoordinates(
                  neighbour_position, ProbabilityType::CREATE_NEW_CHURCH, 0.0);
                continue;
            }

            bool self_in_burning_state =
              askBuildingAtCoordinatesIsInState(source_position, "Burning");
            bool neighbour_in_close_neighbourhood = (i * i + j * j <= 2);
            bool neighbour_in_normal_state =
              askBuildingAtCoordinatesIsInState(neighbour_position, "Normal");
            bool is_cell_probability_already_set = askProbabilityTypePercentageIsSetAtCoordinates(
              neighbour_position, ProbabilityType::SET_CURRENT_BUILDING_ON_FIRE);
            if (self_in_burning_state && neighbour_in_close_neighbourhood &&
                neighbour_in_normal_state && !is_cell_probability_already_set)
            {
                setCellPercentageOfProbabilityAtCoordinates(
                  neighbour_position,
                  ProbabilityType::SET_CURRENT_BUILDING_ON_FIRE,
                  set_adjacent_building_on_fire);
            }

            bool self_in_normal_state =
              askBuildingAtCoordinatesIsInState(source_position, "Normal");
            if (neighbour_in_normal_state && self_in_normal_state)
            {
                for (auto const& [probability_type, _] : probability_default_percentages)
                {
                    double current_probability = askProbabilityTypePercentageAtCoordinates(
                      neighbour_position, probability_type);
                    double new_probability = current_probability * church_probability_multiplier;
                    if (new_probability > 1.0)
                    {
                        new_probability = 1.0;
                    }

                    setCellPercentageOfProbabilityAtCoordinates(
                      neighbour_position, probability_type, new_probability);
                }
            }
        }
    }
}
