#pragma once
#include <cstdint>

namespace StateConstants
{
constexpr unsigned int TimeToLiveDecayValue = 20;
}

enum class BuildingState : std::uint8_t
{
    BURNING,
    NORMAL,
    RUIN,
};

namespace InitialTimeToLive
{
inline constexpr unsigned int Normal = 3700;
inline constexpr unsigned int Burning = 200;
inline constexpr unsigned int Ruin = 560;

}

class State
{
    BuildingState state_name{ BuildingState::NORMAL };
    unsigned int time_to_live{ InitialTimeToLive::Normal };

  public:
    State() = default;

    [[nodiscard]]
    auto getTimeToLive() const -> unsigned int;

    void setTimeToLive(unsigned int supplied_time_to_live);

    [[nodiscard]]
    auto getBuildingState() const -> BuildingState;

    // sets state and initial time to live
    void setBuildingState(BuildingState state_name);

    void doDecay();

    void resetTimeToLive();
};
