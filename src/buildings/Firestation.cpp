#include "Firestation.hpp"
#include "Coordinates.hpp"
#include "World.hpp"
#include <iostream>

auto Firestation::getBuildingType() const -> BuildingType
{
    return BuildingType::FIRESTATION;
}

void Firestation::applyProbabilities(
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
            bool neighbour_is_source = (neighbour_position.x == source_position.x &&
                                        neighbour_position.y == source_position.y);
            if (neighbour_is_source)
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
                setCellPercentageOfProbabilityAtCoordinates(
                  neighbour_position, ProbabilityType::SET_CURRENT_BUILDING_ON_FIRE, 0.0);
                bool self_in_normal_state =
                  askBuildingAtCoordinatesIsInState(source_position, "Normal");
                if (!self_in_normal_state)
                {
                    setCellPercentageOfProbabilityAtCoordinates(
                      neighbour_position, ProbabilityType::SET_CURRENT_BUILDING_ON_FIRE, 0.0);
                }
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
                  neighbour_position, ProbabilityType::CREATE_NEW_FIRESTATION, 0.0);
                continue;
            }

            bool self_in_normal_state =
              askBuildingAtCoordinatesIsInState(neighbour_position, "Normal");
            if (self_in_normal_state)
            {
                setCellPercentageOfProbabilityAtCoordinates(
                  Coordinates(i, j), ProbabilityType::SET_CURRENT_BUILDING_ON_FIRE, 0.0);
            }
        }
    }
}