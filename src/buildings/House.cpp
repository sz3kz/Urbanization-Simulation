#include "House.hpp"
#include "Coordinates.hpp"
#include "World.hpp"
#include <iostream>

constexpr double another_house_in_the_neighbourhood_new_building_probability_decline = 0.0015;
constexpr double house_in_the_neighbourhood_new_building_probability_initial_percentage = 0.01;

auto House::getBuildingType() const -> BuildingType
{
    return BuildingType::HOUSE;
}

void House::applyProbabilities(
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
            if (!empty)
            {
                bool self_is_on_fire = (getStateName() == "Burning");
                bool in_closes_neighbourhood = (i * i + j * j <= 2);
                bool is_ruin = askBuildingAtCoordinatesIsInState(Coordinates(i, j), "Ruin");
                bool is_on_fire = askBuildingAtCoordinatesIsInState(Coordinates(i, j), "Burning");
                bool is_cell_probability_already_set =
                  askProbabilityTypePercentageIsSetAtCoordinates(
                    Coordinates(i, j), ProbabilityType::SET_CURRENT_BUILDING_ON_FIRE);
                if (self_is_on_fire && in_closes_neighbourhood && !is_ruin && !is_on_fire &&
                    !is_cell_probability_already_set)
                {
                    setCellPercentageOfProbabilityAtCoordinates(
                      Coordinates(i, j),
                      ProbabilityType::SET_CURRENT_BUILDING_ON_FIRE,
                      set_adjacent_building_on_fire);
                }
            }

            bool is_self_normal = askBuildingAtCoordinatesIsInState(Coordinates(0, 0), "Normal");
            if (!is_self_normal)
            {
                continue;
            }
            /* Only if house is normal! */
            bool is_cell_probability_already_set = askProbabilityTypePercentageIsSetAtCoordinates(
              Coordinates(i, j), ProbabilityType::CREATE_NEW_HOUSE);
            if (is_cell_probability_already_set)
            {
                double current_probability = askProbabilityTypePercentageAtCoordinates(
                  Coordinates(i, j), ProbabilityType::CREATE_NEW_HOUSE);
                double new_probability =
                  current_probability -
                  another_house_in_the_neighbourhood_new_building_probability_decline;
                if (new_probability < 0.0)
                {
                    new_probability = 0.0;
                }
                setCellPercentageOfProbabilityAtCoordinates(
                  Coordinates(i, j), ProbabilityType::CREATE_NEW_HOUSE, new_probability);
            }
            else
            {
                setCellPercentageOfProbabilityAtCoordinates(
                  Coordinates(i, j),
                  ProbabilityType::CREATE_NEW_HOUSE,
                  house_in_the_neighbourhood_new_building_probability_initial_percentage);
            }
        }
    }
}