#include "Firestation.hpp"
#include "../../include/Building.hpp"
#include "Coordinates.hpp"

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
                setCellPercentageOfProbabilityAtCoordinates(
                  Coordinates(i, j), ProbabilityType::SET_CURRENT_BUILDING_ON_FIRE, 0.0);
                bool is_normal =
                  askBuildingAtCoordinatesIsInState(Coordinates(i, j), BuildingState::NORMAL);
                if (!is_normal)
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
              askBuildingAtCoordinatesIsInState(neighbour_position, BuildingState::NORMAL);
            if (self_in_normal_state)
            {
                setCellPercentageOfProbabilityAtCoordinates(
                  Coordinates(i, j), ProbabilityType::SET_CURRENT_BUILDING_ON_FIRE, 0.0);
            }
        }
    }
}