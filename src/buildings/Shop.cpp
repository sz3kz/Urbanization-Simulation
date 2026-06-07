#include "Shop.hpp"
#include "Coordinates.hpp"

auto Shop::getBuildingType() const -> BuildingType
{
    return BuildingType::SHOP;
}

void Shop::applyProbabilities(
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
                bool self_in_normal_state =
                  askBuildingAtCoordinatesIsInState(Coordinates(i, j), BuildingState::NORMAL);
                if (self_in_normal_state)
                {
                    setCellPercentageOfProbabilityAtCoordinates(
                      neighbour_position,
                      ProbabilityType::RESTORE_TIME_TO_LIVE,
                      ShopConstants::RestoreTimeToLiveBoost);
                }
                else
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

            bool neightbour_is_empty = askCellEmptyAtCoordinates(neighbour_position);
            if (neightbour_is_empty)
            {
                setCellPercentageOfProbabilityAtCoordinates(
                  neighbour_position, ProbabilityType::CREATE_NEW_SHOP, 0.0);
                continue;
            }

            bool self_in_burning_state =
              askBuildingAtCoordinatesIsInState(source_position, BuildingState::BURNING);
            bool neighbour_in_close_neighbourhood = ((i * i) + (j * j) <= 2);
            bool neighbour_in_normal_state =
              askBuildingAtCoordinatesIsInState(Coordinates(i, j), BuildingState::NORMAL);
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
              askBuildingAtCoordinatesIsInState(Coordinates(0, 0), BuildingState::NORMAL);
            if (neighbour_in_normal_state && self_in_normal_state)
            {
                setCellPercentageOfProbabilityAtCoordinates(neighbour_position,
                                                            ProbabilityType::RESTORE_TIME_TO_LIVE,
                                                            ShopConstants::RestoreTimeToLiveBoost);
            }
        }
    }
}
