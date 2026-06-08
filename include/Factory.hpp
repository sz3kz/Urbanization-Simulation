#pragma once

#include "Building.hpp"
#include "Coordinates.hpp"
#include "Emoji.hpp"
#include <functional>

/**
 * @brief Constants used by factory probability calculations.
 */
namespace FactoryConstants
{
/**
 * @brief Probability assigned for restoring a ruined building.
 */
inline constexpr double RestoreFromRuinProbabilityBoost{ 0.3 };
}

/**
 * @brief Factory building.
 *
 * A factory influences cells within its radius by modifying
 * restoration and fire-related probabilities.
 *
 * Factories prevent nearby empty cells from creating additional
 * factories and can contribute to fire propagation and ruin
 * restoration events.
 */
class Factory : public Building
{
  public:
    /**
     * @brief Constructs a factory.
     *
     * Initializes:
     * - Emoji::Factory as the visual representation.
     * - BuildingRadiusConstants::Factory as the influence radius.
     */

    explicit Factory()
      : Building(Emoji::Factory, BuildingRadiusConstants::Factory)
    {
    }

    /**
     * @brief Returns the building type identifier.
     *
     * @return BuildingType::FACTORY.
     */
    [[nodiscard]]
    auto getBuildingType() const -> BuildingType override;

    /**
     * @brief Applies factory-specific probability effects.
     *
     * For each cell within the factory's influence radius:
     *
     * - Empty cells are prevented from creating another factory.
     * - A burning factory may increase the probability that nearby
     *   buildings catch fire.
     * - A factory may increase the probability that ruined
     *   buildings are restored.
     *
     * The supplied callbacks provide controlled access to board
     * state and probability values.
     *
     * @param askCellExistsAtCoordinates Checks whether coordinates exist.
     * @param askCellEmptyAtCoordinates Checks whether a cell is empty.
     * @param askProbabilityTypePercentageIsSetAtCoordinates Checks whether a probability value was
     * already modified during this iteration.
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