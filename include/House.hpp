#pragma once
#include "Building.hpp"
#include "Coordinates.hpp"
#include <functional>

class House : public Building
{
    unsigned int radius;

  public:
    explicit House(unsigned int supplied_radius)
      : radius(supplied_radius) {};
    [[nodiscard]]
    auto getBuildingType() const -> BuildingType override;
    [[nodiscard]]
    auto getBuildingImage() const -> std::string override;

    void applyProbabilities(
      std::function<bool(Coordinates)> askCellExistsAtCoordinates,
      std::function<bool(Coordinates)> askCellEmptyAtCoordinates,
      std::function<bool(Coordinates, ProbabilityType)>
        askProbabilityTypePercentageIsSetAtCoordinates,
      std::function<double(Coordinates, ProbabilityType)> askProbabilityTypePercentageAtCoordinates,
      std::function<void(Coordinates, ProbabilityType, double)>
        setCellPercentageOfProbabilityAtCoordinates) override;
};
