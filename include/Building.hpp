#pragma once
#include "CellProbabilities.hpp"
#include "Coordinates.hpp"
#include "State.hpp"
#include <functional>
#include <memory>
#include <utility>

/**
 * @brief Enumerates all supported building types.
 */
enum class BuildingType : std::uint8_t
{
    SHOP,
    HOUSE,
    FIRESTATION,
    FACTORY,
    CHURCH,
};

/**
 * @brief Constants defining infuence radiuses of building-derived
 * classes.
 * Used when constructing a specific building.
 */
namespace BuildingRadiusConstants
{
inline constexpr unsigned int House{ 2 };
inline constexpr unsigned int Shop{ 4 };
inline constexpr unsigned int Firestation{ 6 };
inline constexpr unsigned int Factory{ 4 };
inline constexpr unsigned int Church{ 4 };
}

/**
 * @brief Abstract base class representing a building on the board.
 *
 * A Building has:
 * - A visual emoji representation.
 * - An influence radius.
 * - A state object
 *
 * Concrete building types must derive from this class and implement:
 * - getBuildingType()
 * - applyProbabilities()
 *
 * Building objects are intended to be managed through
 * std::unique_ptr<Building>.
 */
class Building
{
    std::string emoji{ "❌" };             ///< Emoji used when rendering the building.
    unsigned int radius{ 0 };              ///< Area-of-effect radius.
    std::unique_ptr<State> building_state; ///< Lifecycle state.

  protected:
    /**
     * @brief Returns the building influence radius.
     *
     * @return Radius of influence of building object
     */
    [[nodiscard]]
    auto getRadius() const -> unsigned int;

  public:
    /**
     * @brief Constructs a building with a default state(normal).
     *
     * @param supplied_emoji Building's unique emoji
     * @param supplied_radius Building's radius value
     */
    Building(std::string supplied_emoji, unsigned int supplied_radius)
      : emoji(std::move(supplied_emoji))
      , radius(supplied_radius)
      , building_state(std::make_unique<State>())
    {
    }
    /**
     * @brief Virtual destructor.
     */
    virtual ~Building() = default;

    /// @name Non-copyable and non-movable
    /// @{
    Building(Building const&) = delete;
    auto operator=(Building const&) -> Building& = delete;
    Building(Building&&) = delete;
    auto operator=(Building&&) -> Building& = delete;
    /// @}

    /**
     * @brief Classic getter to the building type of the cell's occupant.
     *
     * @return Type identifier of the derived building
     */
    [[nodiscard]]
    virtual auto getBuildingType() const -> BuildingType = 0;

    /**
     * @brief Classic getter to the building state of the cell's occupant.
     *
     * @return Current BuildingState value
     */
    [[nodiscard]]
    auto getBuildingState() const -> BuildingState;

    /**
     * @brief Classic setter of the building state of the cell's occupant.
     *
     * @param supplied_building_state New state
     */
    void setBuildingState(BuildingState const& supplied_building_state) const;

    /**
     * @brief Classic getter to the building state's Time To Live.
     *
     * @return Remaining time-to-live value.
     */
    [[nodiscard]]
    auto getTimeToLive() const -> unsigned int;

    /**
     * @brief Advances the building decay process.
     *
     * Delegates decay logic to the internal State object.
     */
    void decay() const;

    /**
     * @brief Restores the building's time-to-live value.
     */
    void resetTimeToLive() const;

    /**
     * @brief Implements building specific algorithm for probability propagation.
     *
     * Derived classes use this function to set probability values in
     * the probability board with their algorithm.
     *
     * The supplied callbacks provide controlled access to board
     * state without exposing board internals directly(with nice relative coordinate handing :D)
     *
     * @param askCellExistsAtCoordinates Checks whether a coordinate exists.
     * @param askCellEmptyAtCoordinates Checks whether a cell is empty.
     * @param askProbabilityTypePercentageIsSetAtCoordinates Checks whether a probability value was
     * already modified during this iteration.
     * @param askProbabilityTypePercentageAtCoordinates Retrieves a probability value.
     * @param setCellPercentageOfProbabilityAtCoordinates Stores a probability value.
     * @param askBuildingAtCoordinatesIsInState Checks whether a building is in a.
     *        specific state.
     */
    virtual void applyProbabilities(
      [[maybe_unused]] std::function<bool(Coordinates)> askCellExistsAtCoordinates,
      [[maybe_unused]] std::function<bool(Coordinates)> askCellEmptyAtCoordinates,
      [[maybe_unused]] std::function<bool(Coordinates, ProbabilityType)>
        askProbabilityTypePercentageIsSetAtCoordinates,
      [[maybe_unused]] std::function<double(Coordinates, ProbabilityType)>
        askProbabilityTypePercentageAtCoordinates,
      [[maybe_unused]] std::function<void(Coordinates, ProbabilityType, double)>
        setCellPercentageOfProbabilityAtCoordinates,
      [[maybe_unused]] std::function<bool(Coordinates, BuildingState)>
        askBuildingAtCoordinatesIsInState) = 0;

    /**
     * @brief Genius-Level operator<< overloading for nice output syntax.
     *
     * Output depends on the current building state:
     * - RUIN    -> Derelict house emoji
     * - BURNING -> Fire emoji
     * - NORMAL  -> Building-specific emoji
     *
     * @param os Output stream.
     * @param building Building to render.
     * @return Reference to the output stream.
     */
    friend auto operator<<(std::ostream& os, const Building& building) -> std::ostream&;
};