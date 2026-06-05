#include "Church.hpp"
#include "../../include/Building.hpp"
#include "CellProbabilities.hpp"
#include "Coordinates.hpp"
#include "World.hpp"

#include <algorithm>
#include <iostream>
#include <ranges>

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
  [[maybe_unused]] std::function<bool(Coordinates, BuildingState)>
    askBuildingAtCoordinatesIsInState)
{
    int signed_radius = static_cast<int>(this->getRadius());
    for (int i = (-1) * signed_radius; i <= signed_radius; ++i)
    {
        for (int j = (-1) * signed_radius; j <= signed_radius; ++j)
        {
            Coordinates neighbour_position(i, j);
            Coordinates source_position(0, 0);
            if (neighbour_position == source_position)
            {
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
              askBuildingAtCoordinatesIsInState(source_position, BuildingState::BURNING);
            bool neighbour_in_close_neighbourhood = ((i * i) + (j * j) <= 2);
            // bool is_ruin =
            // askBuildingAtCoordinatesIsInState(Coordinates(i, j), BuildingState::RUIN);
            // bool is_on_fire =
            // askBuildingAtCoordinatesIsInState(Coordinates(i, j), BuildingState::BURNING);
            bool neighbour_in_normal_state =
              askBuildingAtCoordinatesIsInState(neighbour_position, BuildingState::NORMAL);
            bool is_cell_probability_already_set = askProbabilityTypePercentageIsSetAtCoordinates(
              neighbour_position, ProbabilityType::SET_CURRENT_BUILDING_ON_FIRE);
            if (self_in_burning_state && neighbour_in_close_neighbourhood &&
                neighbour_in_normal_state && !is_cell_probability_already_set)
            {
                setCellPercentageOfProbabilityAtCoordinates(
                  neighbour_position,
                  ProbabilityType::SET_CURRENT_BUILDING_ON_FIRE,
                  OccupiedCellDefaultProbabilities::SetAdjacentBuildingOnFire);
            }

            bool self_in_normal_state =
              askBuildingAtCoordinatesIsInState(source_position, BuildingState::NORMAL);
            if (neighbour_in_normal_state && self_in_normal_state)
            {
                for (const auto& probability_type : {
                       ProbabilityType::CREATE_NEW_HOUSE,
                       ProbabilityType::CREATE_NEW_FIRESTATION,
                       ProbabilityType::CREATE_NEW_SHOP,
                       ProbabilityType::CREATE_NEW_FACTORY,
                       ProbabilityType::CREATE_NEW_CHURCH,
                       ProbabilityType::SET_CURRENT_BUILDING_ON_FIRE,
                       ProbabilityType::RESTORE_TIME_TO_LIVE,
                       ProbabilityType::RESTORE_FROM_RUIN,
                     })
                {
                    double current_probability = askProbabilityTypePercentageAtCoordinates(
                      neighbour_position, probability_type);
                    double new_probability =
                      std::min(current_probability * ChurchConstants::ProbabilityMultiplier, 1.0);

                    setCellPercentageOfProbabilityAtCoordinates(
                      neighbour_position, probability_type, new_probability);
                }
            }
        }
    }
}
