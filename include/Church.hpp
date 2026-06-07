#pragma once
#include "Building.hpp"
#include "Coordinates.hpp"
#include "Emoji.hpp"
#include <functional>

/**
 * @brief Constants used by Church probability calculations.
 */
namespace ChurchConstants
{
/**
 * @brief Multiplier applied to neighbouring probabilities.
 *
 * Probability values are multiplied by this factor and capped at 1.0.
 */
inline constexpr unsigned long ProbabilityMultiplier{ 100 };
}

/**
 * @brief Church building.
 *
 * A church influences buildings within its radius by increasing
 * their probability values. When both the church and a neighbouring
 * building are in the NORMAL state, the neighbour's probabilities
 * are amplified by ChurchConstants::ProbabilityMultiplier.
 *
 * A burning church can also spread fire to nearby buildings.
 */
class Church : public Building
{
  public:
    /**
     * @brief Constructs a church.
     *
     * Initializes:
     * - Emoji::Church as the visual representation.
     * - BuildingRadiusConstants::Church as the influence radius.
     */
    explicit Church()
    {
        setEmoji(Emoji::Church);
        setRadius(BuildingRadiusConstants::Church);
    }

    /**
     * @brief Returns the building type identifier.
     *
     * @return BuildingType::CHURCH.
     */
    [[nodiscard]]
    auto getBuildingType() const -> BuildingType override;

    /**
     * @brief Applies church-specific probability effects.
     *
     * For each cell within the church's influence radius:
     *
     * - Empty cells are prevented from creating another church.
     * - If this church is burning, nearby NORMAL buildings may be
     *   marked as candidates for catching fire.
     * - If both this church and a neighbouring building are in the
     *   NORMAL state, all of the neighbour's probability values are
     *   multiplied by ChurchConstants::ProbabilityMultiplier and
     *   capped at 1.0.
     *
     * The supplied callbacks provide access to board state and
     * probability values without directly exposing board internals.
     *
     * @param askCellExistsAtCoordinates Checks whether coordinates exist.
     * @param askCellEmptyAtCoordinates Checks whether a cell is empty.
     * @param askProbabilityTypePercentageIsSetAtCoordinates Checks whether a probability value was
     * already modified during this iteration.
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