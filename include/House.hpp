#pragma once
#include "Building.hpp"
#include "Coordinates.hpp"
#include <functional>

namespace HouseConstants
{
inline constexpr double AnotherHouseInTheNeighbourhoodNewBuildingProbabilityDecline{ 0.0015 };
inline constexpr double HouseInTheNeighbourhoodNewBuildingProbabilityInitialPercentage{ 0.01 };
}

class House : public Building
{

  public:
    explicit House()
    {
        setEmoji(Emoji::House);
        setRadius(BuildingRadiusConstants::House);
    };

    [[nodiscard]]
    auto getBuildingType() const -> BuildingType override;

    void applyProbabilities(
      [[maybe_unused]] std::function<bool(Coordinates)> askCellExistsAtCoordinates,
      [[maybe_unused]] std::function<bool(Coordinates)> askCellEmptyAtCoordinates,
      [[maybe_unused]] std::function<bool(Coordinates, ProbabilityType)>
        askProbabilityTypePercentageIsSetAtCoordinates,
      [[maybe_unused]] std::function<double(Coordinates, ProbabilityType)>
        askProbabilityTypePercentageAtCoordinates,
      [[maybe_unused]] std::function<void(Coordinates, ProbabilityType, double)>
        setCellPercentageOfProbabilityAtCoordinates,
      [[maybe_unused]] std::function<bool(Coordinates, BuildingState)>
        askBuildingAtCoordinatesIsInState) override;
};
