#pragma once
#include <cstdint>

/**
 * @brief Constants used by the building state system.
 */
namespace StateConstants
{
/**
 * @brief Amount subtracted from a state's time-to-live during each decay step.
 */
constexpr unsigned int TimeToLiveDecayValue{ 20 };
}

/**
 * @brief Possible lifecycle states of a building.
 */
enum class BuildingState : std::uint8_t
{
    BURNING, ///< Building is on fire.
    NORMAL,  ///< Building is operating normally.
    RUIN,    ///< Building has been destroyed.
};

/**
 * @brief Default time-to-live values assigned to each building state.
 *
 * Whenever a building enters a new state, its lifetime counter is
 * reset to the corresponding value.
 */
namespace InitialTimeToLive
{
/// Initial lifetime of a normal building.
inline constexpr unsigned int Normal{ 3700 };

/// Initial lifetime of a burning building.
inline constexpr unsigned int Burning{ 200 };

/// Initial lifetime of a ruined building.
inline constexpr unsigned int Ruin{ 560 };
}

/**
 * @brief Stores the lifecycle state of a building.
 *
 * A State object tracks:
 * - The current BuildingState.
 * - The remaining time-to-live associated with that state.
 *
 * When the state changes, the time-to-live is automatically reset
 * to the default value defined in InitialTimeToLive.
 */
class State
{
    /**
     * @brief Current lifecycle state.
     * Default initialized to normal.
     */
    BuildingState state_name{ BuildingState::NORMAL };

    /**
     * @brief Remaining time-to-live for the current state.
     * Same as state_name
     */
    unsigned int time_to_live{ InitialTimeToLive::Normal };

  public:
    /**
     * @brief Constructs a state in the NORMAL state.
     */
    State() = default;

    /**
     * @brief Returns the remaining time-to-live.
     *
     * @return Remaining lifetime value.
     */
    [[nodiscard]]
    auto getTimeToLive() const -> unsigned int;

    /**
     * @brief Returns the current building state.
     *
     * @return Current BuildingState value.
     */
    [[nodiscard]]
    auto getBuildingState() const -> BuildingState;

    /**
     * @brief Changes the current building state.
     *
     * The time-to-live is automatically reset to the default value
     * associated with the supplied state.
     *
     * @param state_name New state.
     */
    void setBuildingState(BuildingState state_name);

    /**
     * @brief Applies state decay.
     *
     * Decreases the remaining time-to-live by
     * StateConstants::TimeToLiveDecayValue.
     */
    void doDecay();

    /**
     * @brief Resets the time-to-live for the current state.
     *
     * The value is selected from InitialTimeToLive according to
     * the current BuildingState.
     */
    void resetTimeToLive();
};