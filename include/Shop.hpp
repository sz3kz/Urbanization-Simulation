#pragma once

#include "Building.hpp"
#include "Coordinates.hpp"
#include "Emoji.hpp"
#include <functional>

/**
 * @brief Constants used by shop probability calculations.
 */
namespace ShopConstants
{
/**
 * @brief Probability boost applied when restoring building lifetime.
 *
 * A value of 1.0 guarantees restoration when selected during
 * probability evaluation.
 */
inline constexpr double RestoreTimeToLiveBoost{ 1.0 };
}

/**
 * @brief Shop maintains nearby structures.
 *
 * Shops increase the probability of restoring the time-to-live of
 * neighbouring buildings. This helps keep buildings operational for
 * longer periods.
 *
 * When burning, a shop can also spread fire to nearby buildings in
 * its immediate neighbourhood.
 */
class Shop : public Building
{
  public:
    /**
     * @brief Constructs a shop.
     *
     * Initializes:
     * - Emoji::Shop as the visual representation.
     * - BuildingRadiusConstants::Shop as the influence radius.
     */
    explicit Shop()
    {
        setEmoji(Emoji::Shop);
        setRadius(BuildingRadiusConstants::Shop);
    }

    /**
     * @brief Returns the building type identifier.
     *
     * @return BuildingType::SHOP.
     */
    [[nodiscard]]
    auto getBuildingType() const -> BuildingType override;

    /**
     * @brief Applies shop-specific probability effects.
     *
     * For each cell within the shop's influence radius:
     *
     * - Empty cells are prevented from spawning another shop.
     * - A burning shop may ignite nearby NORMAL buildings.
     * - A NORMAL shop increases the probability of restoring
     *   time-to-live for nearby NORMAL buildings.
     * - The shop itself receives a time-to-live restoration
     *   probability while in the NORMAL state.
     *
     * The supplied callback functions provide controlled access to
     * board state and probability values without exposing the board
     * implementation.
     *
     * @param askCellExistsAtCoordinates Checks whether coordinates exist.
     * @param askCellEmptyAtCoordinates Checks whether a cell is empty.
     * @param askProbabilityTypePercentageIsSetAtCoordinates Checks whether a
     *        probability value has already been assigned.
     * @param askProbabilityTypePercentageAtCoordinates Retrieves a probability value.
     * @param setCellPercentageOfProbabilityAtCoordinates Updates a probability value.
     * @param askBuildingAtCoordinatesIsInState Checks a building's state.
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