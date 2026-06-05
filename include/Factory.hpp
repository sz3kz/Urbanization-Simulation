#pragma once
#include "Building.hpp"
#include "Coordinates.hpp"
#include "Emoji.hpp"
#include <functional>

namespace FactoryConstants
{
inline constexpr double RestoreFromRuinProbabilityBoost{ 0.3 };
}

class Factory : public Building
{

  public:
    explicit Factory()
    {
        setEmoji(Emoji::Factory);
        setRadius(BuildingRadiusConstants::Factory);
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
