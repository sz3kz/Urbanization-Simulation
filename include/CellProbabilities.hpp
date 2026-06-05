#pragma once
#include <cstdint>
#include <map>

/**
 * @brief Default probabilities assigned to empty cells.
 *
 * These values are used when a CellProbabilities object is
 * initialized with CellState::Empty, like when creating the
 * probability board.
 */
namespace EmptyCellDefaultProbabilities
{
/// Probability of creating a new house.
inline constexpr double CreateNewHouse{ 0.001 };

/// Probability of creating a new fire station.
inline constexpr double CreateNewFirestation{ 0.00001 };

/// Probability of creating a new shop.
inline constexpr double CreateNewShop{ 0.00001 };

/// Probability of creating a new factory.
inline constexpr double CreateNewFactory{ 0.00001 };

/// Probability of creating a new church.
inline constexpr double CreateNewChurch{ 0.00001 };

/// Empty cells cannot catch fire.
inline constexpr double SetCurrentBuildingOnFire{ 0.0 };

/// Empty cells cannot be restored from ruin.
inline constexpr double RestoreBuildingFromRuin{ 0 };

/// Empty cells have no building lifetime to restore.
inline constexpr double RestoreBuildingTimeToLive{ 0 };
}

/**
 * @brief Default probabilities assigned to occupied cells.
 *
 * These values are used when a CellProbabilities object is
 * initialized with CellState::Occupied, like when resetting
 * the probability board.
 */
namespace OccupiedCellDefaultProbabilities
{
/// An occupied cell has not space for House.
inline constexpr double CreateNewHouse{ 0.0 };

/// An occupied cell has not space for Firestation.
inline constexpr double CreateNewFirestation{ 0.0 };

/// An occupied cell has not space for Shop.
inline constexpr double CreateNewShop{ 0.0 };

/// An occupied cell has not space for Factory.
inline constexpr double CreateNewFactory{ 0.0 };

/// An occupied cell has not space for Church.
inline constexpr double CreateNewChurch{ 0.0 };

/// Probability that the current building catches fire.
inline constexpr double SetCurrentBuildingOnFire{ 0.0001 };

/// By default building should not self-restore from ruin.
inline constexpr double RestoreBuildingFromRuin{ 0 };

/// By default building should not self-restore from ruin.
inline constexpr double RestoreBuildingTimeToLive{ 0 };

/// Probability that fire spreads to an adjacent building.
inline constexpr double SetAdjacentBuildingOnFire{ 0.8 };
}

/**
 * @brief Describes whether a board cell is occupied.
 */
enum class CellState : uint8_t
{
    Empty,   ///< Cell contains no building.
    Occupied ///< Cell contains a building.
};

/**
 * @brief Identifies a probability stored within a cell.
 *
 * Each entry corresponds to a possible event that may occur
 * during simulation iterations.
 */
enum class ProbabilityType : std::uint8_t
{
    CREATE_NEW_HOUSE,             ///< Create a new house.
    CREATE_NEW_FIRESTATION,       ///< Create a new fire station.
    CREATE_NEW_SHOP,              ///< Create a new shop.
    CREATE_NEW_FACTORY,           ///< Create a new factory.
    CREATE_NEW_CHURCH,            ///< Create a new church.
    SET_CURRENT_BUILDING_ON_FIRE, ///< Ignite the current building.
    RESTORE_TIME_TO_LIVE,         ///< Restore building lifetime.
    RESTORE_FROM_RUIN,            ///< Restore a ruined building.
};

/**
 * @brief Stores a probability value and its last modification iteration.
 *
 * The iteration value can be used to determine whether the
 * probability has already been computed for a simulation step.
 */
struct Probability
{
    /**
     * @brief Iteration during which the probability was last updated.
     */
    unsigned long last_updated_at_iteration;

    /**
     * @brief Probability value.
     */
    double value;
};

/**
 * @brief Stores all probabilities associated with a single board cell.
 *
 * Each ProbabilityType is mapped to a Probability structure
 * containing both the probability value and the iteration in
 * which it was last computed.
 */
struct CellProbabilities
{
    /**
     * @brief Collection of probability values indexed by event type.
     */
    std::map<ProbabilityType, Probability> probabilities;

    /**
     * @brief Constructs a probability set using defaults for the given cell state.
     *
     * Empty and occupied cells receive different default probability values.
     *
     * @param state Initial occupancy state of the cell
     *
     * @throws std::invalid_argument if unknown state is supplied
     */
    explicit CellProbabilities(CellState state);

    /**
     * @brief Constructs probabilities for an empty cell.
     * Needed for some default thing with vectors and stuff.
     *
     * Equivalent to:
     * @code
     * CellProbabilities(CellState::Empty)
     * @endcode
     */
    CellProbabilities()
      : CellProbabilities(CellState::Empty)
    {
    }
};