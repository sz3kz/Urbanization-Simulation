#pragma once
#include "Coordinates.hpp"
#include "World.hpp"
#include <functional>

// virtual <return-type> func(<parameters>) = 0
//  Pure virtual function: don't implement it here, force implementation at child,
//  disallow direct Building object instatiation.

class Building
{
  public:
    /* Virtual destructor
     * Can aid in childclass identification via dynamic_cast.
     * Since we use the Building::getBuildingType() function to identify childclasses
     *  this is not really needed
     */
    virtual ~Building() = default;

    /* Disable all other special methods*/
    Building(Building const&) = delete;
    auto operator=(Building const&) -> Building& = delete;
    Building(Building&&) = delete;
    auto operator=(Building&&) -> Building& = delete;

    [[nodiscard]]
    virtual auto getBuildingType() const -> BuildingType = 0;
    // Function that populates probability_board with probabilities
    virtual void applyProbabilities(
      std::function<bool(Coordinates)> askCellExistsAtCoordinates,
      std::function<bool(Coordinates)> askCellEmptyAtCoordinates,
      std::function<bool(Coordinates, ProbabilityType)>
        askProbabilityTypePercentageIsSetAtCoordinates,
      std::function<double(Coordinates, ProbabilityType)> getProbabilityTypePercentageAtCoordinates,
      std::function<void(Coordinates, ProbabilityType, double)>
        setProbabilityTypePercentageAtCoordinates) = 0;

  protected:
    Building() = default;
};