#include "State.hpp"

auto State::getTimeToLive() const -> unsigned int
{
    return this->time_to_live;
}
void State::setTimeToLive(unsigned int supplied_time_to_live)
{
    this->time_to_live = supplied_time_to_live;
}

auto State::getBuildingState() const -> BuildingState
{
    return this->state_name;
}
// sets state and initial time to live
void State::setBuildingState(BuildingState supplied_state_name)
{
    this->state_name = supplied_state_name;
    resetTimeToLive();
}

void State::doDecay()
{
    time_to_live -= StateConstants::TimeToLiveDecayValue;
}

void State::resetTimeToLive()
{
    switch (state_name)
    {
        case BuildingState::NORMAL:
        {
            this->time_to_live = InitialTimeToLive::Normal;
            break;
        }
        case BuildingState::BURNING:
        {
            this->time_to_live = InitialTimeToLive::Burning;
            break;
        }
        case BuildingState::RUIN:
        {
            this->time_to_live = InitialTimeToLive::Ruin;
            break;
        }
    }
}
