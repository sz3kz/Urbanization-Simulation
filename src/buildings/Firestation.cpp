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
            bool is_self = (i == 0 && j == 0);
            if (is_self)
            {
                setCellPercentageOfProbabilityAtCoordinates(
                  Coordinates(i, j), ProbabilityType::CREATE_NEW_HOUSE, 0.0);
                setCellPercentageOfProbabilityAtCoordinates(
                  Coordinates(i, j), ProbabilityType::CREATE_NEW_FIRESTATION, 0.0);
                setCellPercentageOfProbabilityAtCoordinates(
                  Coordinates(i, j), ProbabilityType::CREATE_NEW_SHOP, 0.0);
                setCellPercentageOfProbabilityAtCoordinates(
                  Coordinates(i, j), ProbabilityType::CREATE_NEW_FACTORY, 0.0);
                setCellPercentageOfProbabilityAtCoordinates(
                  Coordinates(i, j), ProbabilityType::CREATE_NEW_CHURCH, 0.0);
                setCellPercentageOfProbabilityAtCoordinates(
                  Coordinates(i, j), ProbabilityType::SET_CURRENT_BUILDING_ON_FIRE, 0.0);
                bool is_normal = askBuildingAtCoordinatesIsInState(Coordinates(i, j), "Normal");
                if (!is_normal)
                {
                    setCellPercentageOfProbabilityAtCoordinates(
                      Coordinates(i, j), ProbabilityType::SET_CURRENT_BUILDING_ON_FIRE, 0.0);
                }
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
                setCellPercentageOfProbabilityAtCoordinates(
                  Coordinates(i, j), ProbabilityType::CREATE_NEW_FIRESTATION, 0.0);
                continue;
            }

            bool self_is_normal = askBuildingAtCoordinatesIsInState(Coordinates(0, 0), "Normal");
            if (self_is_normal)
            {
                setCellPercentageOfProbabilityAtCoordinates(
                  Coordinates(i, j), ProbabilityType::SET_CURRENT_BUILDING_ON_FIRE, 0.0);
            }

            /*
            setCellPercentageOfProbabilityAtCoordinates(
              Coordinates(i, j), ProbabilityType::CREATE_NEW_FIRESTATION, 0.0);
            */
        }
    }
}