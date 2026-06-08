#pragma once

#include "Building.hpp"
#include "Coordinates.hpp"
#include "Emoji.hpp"
#include <functional>

/**
 * @brief Constants used by house probability calculations.
 */
namespace HouseConstants
{
/**
 * @brief Reduction applied to the house creation probability
 * when another nearby house has already contributed to it.
 */
inline constexpr double AnotherHouseInTheNeighbourhoodNewBuildingProbabilityDecline{ 0.0015 };

/**
 * @brief Initial probability assigned for creating a new house
 * in a neighbouring cell.
 */
inline constexpr double HouseInTheNeighbourhoodNewBuildingProbabilityInitialPercentage{ 0.01 };
}

/**
 * @brief House building.
 *
 * Houses influence nearby cells by encouraging spawning growth.
 * A normal house increases the probability of creating houses in
 * neighbouring locations.
 *
 * Houses may also spread fire to adjacent buildings when burning.
 */
class House : public Building
{
  public:
    /**
     * @brief Constructs a house.
     *
     * Initializes:
     * - Emoji::House as the visual representation.
     * - BuildingRadiusConstants::House as the influence radius.
     */
    explicit House()
      : Building(Emoji::House, BuildingRadiusConstants::House)
    {
    }

    /**
     * @brief Returns the building type identifier.
     *
     * @return BuildingType::HOUSE.
     */
    [[nodiscard]]
    auto getBuildingType() const -> BuildingType override;

    /**
     * @brief Applies house-specific probability effects.
     *
     * For each cell within the house's influence radius:
     *
     * - A burning house may cause nearby NORMAL buildings to catch fire.
     * - Houses that are not in the NORMAL state do not contribute
     *   residential growth probabilities.
     * - A NORMAL house increases the probability of creating houses
     *   in neighbouring cells.
     * - If a neighbouring cell has already received a house creation
     *   probability contribution, that probability is reduced by
     *   HouseConstants::AnotherHouseInTheNeighbourhoodNewBuildingProbabilityDecline.
     * - Otherwise, the probability is initialized to
     *   HouseConstants::HouseInTheNeighbourhoodNewBuildingProbabilityInitialPercentage.
     *
     * The supplied callbacks provide access to board state and
     * probability values without exposing board internals.
     *
     * @param askCellExistsAtCoordinates Checks whether coordinates exist.
     * @param askCellEmptyAtCoordinates Checks whether a cell is empty.
     * @param askProbabilityTypePercentageIsSetAtCoordinates Checks whether a
     *        probability value has already been computed.
     * @param askProbabilityTypePercentageAtCoordinates Retrieves a probability value.
     * @param setCellPercentageOfProbabilityAtCoordinates Updates a probability value.
     * @param askBuildingAtCoordinatesIsInState Checks a building's current state.
     */
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