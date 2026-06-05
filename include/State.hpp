#pragma once
#include "World.hpp"

namespace StateConstants
{
constexpr unsigned int TimeToLiveDecayValue = 20;
}

class State
{
    BuildingState state_name{ BuildingState::NORMAL };
    unsigned int time_to_live{ building_state_initial_time_to_live[BuildingState::NORMAL] };

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
