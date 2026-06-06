#pragma once
#include "Building.hpp"
#include "Coordinates.hpp"
#include "Emoji.hpp"
#include <functional>

/**
 * @brief Fire station building.
 *
 * A fire station reduces the risk of fire within its area of influence.
 * Buildings within its radius have their fire-related probabilities
 * suppressed, making them less likely to enter a burning state.
 *
 * Fire stations also prevent nearby empty cells from creating
 * additional fire stations.
 */
class Firestation : public Building
{
  public:
    /**
     * @brief Constructs a fire station.
     *
     * Initializes:
     * - Emoji::FireTruck as the visual representation.
     * - BuildingRadiusConstants::Firestation as the influence radius.
     */
    explicit Firestation()
    {
        setEmoji(Emoji::FireTruck);
        setRadius(BuildingRadiusConstants::Firestation);
    }

    /**
     * @brief Returns the building type identifier.
     *
     * @return BuildingType::FIRESTATION.
     */
    [[nodiscard]]
    auto getBuildingType() const -> BuildingType override;

    /**
     * @brief Applies fire station probability effects.
     *
     * For each cell within the fire station's influence radius:
     *
     * - Empty cells are prevented from creating another fire station.
     * - The fire probability of the fire station itself is reduced to zero.
     * - Nearby buildings in the NORMAL state have their
     *   SET_CURRENT_BUILDING_ON_FIRE probability reduced to zero.
     *
     * The supplied callbacks provide access to board state and
     * probability values without exposing board internals.
     *
     * @param askCellExistsAtCoordinates Checks whether coordinates exist.
     * @param askCellEmptyAtCoordinates Checks whether a cell is empty.
     * @param askProbabilityTypePercentageIsSetAtCoordinates Checks whether a
     *        probability has already been computed.
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