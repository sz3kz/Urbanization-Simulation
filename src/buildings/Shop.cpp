#include "Shop.hpp"
#include "Coordinates.hpp"
#include "World.hpp"
#include <iostream>

constexpr double shop_restore_time_to_live_boost = 1.0;

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
  [[maybe_unused]] std::function<bool(Coordinates, std::string)> askBuildingAtCoordinatesIsInState)
{
    int signed_radius = static_cast<int>(radius);
    for (int i = (-1) * signed_radius; i <= signed_radius; ++i)
    {
        for (int j = (-1) * signed_radius; j <= signed_radius; ++j)
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
                bool is_normal = askBuildingAtCoordinatesIsInState(Coordinates(i, j), "Normal");
                if (is_normal)
                {
                    setCellPercentageOfProbabilityAtCoordinates(
                      Coordinates(i, j),
                      ProbabilityType::RESTORE_TIME_TO_LIVE,
                      shop_restore_time_to_live_boost);
                }
                else
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
                  Coordinates(i, j), ProbabilityType::CREATE_NEW_SHOP, 0.0);
                continue;
            }

            bool self_is_on_fire = (getStateName() == "Burning");
            bool in_closes_neighbourhood = (i * i + j * j <= 2);
            bool is_ruin = askBuildingAtCoordinatesIsInState(Coordinates(i, j), "Ruin");
            bool is_on_fire = askBuildingAtCoordinatesIsInState(Coordinates(i, j), "Burning");
            bool is_cell_probability_already_set = askProbabilityTypePercentageIsSetAtCoordinates(
              Coordinates(i, j), ProbabilityType::SET_CURRENT_BUILDING_ON_FIRE);
            if (self_is_on_fire && in_closes_neighbourhood && !is_ruin && !is_on_fire &&
                !is_cell_probability_already_set)
            {
                setCellPercentageOfProbabilityAtCoordinates(
                  Coordinates(i, j),
                  ProbabilityType::SET_CURRENT_BUILDING_ON_FIRE,
                  set_adjacent_building_on_fire);
            }

            bool self_is_normal = askBuildingAtCoordinatesIsInState(Coordinates(0, 0), "Normal");
            bool is_normal = askBuildingAtCoordinatesIsInState(Coordinates(i, j), "Normal");
            if (is_normal && self_is_normal)
            {
                setCellPercentageOfProbabilityAtCoordinates(Coordinates(i, j),
                                                            ProbabilityType::RESTORE_TIME_TO_LIVE,
                                                            shop_restore_time_to_live_boost);
            }
        }
    }
}
