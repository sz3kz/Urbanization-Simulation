#pragma once
#include "Building.hpp"
#include "Coordinates.hpp"
#include "Emoji.hpp"
#include <functional>

namespace ChurchConstants
{
inline constexpr unsigned long ProbabilityMultiplier{ 100 };
}

class Church : public Building
{

  public:
    explicit Church()
    {
        setEmoji(Emoji::Church);
        setRadius(BuildingRadiusConstants::Church);
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