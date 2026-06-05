#pragma once
#include "Building.hpp"
#include "Coordinates.hpp"
#include "Emoji.hpp"
#include <functional>

class Firestation : public Building
{

  public:
    explicit Firestation()
    {
        setEmoji(Emoji::FireTruck);
        setRadius(BuildingRadiusConstants::Firestation);
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
