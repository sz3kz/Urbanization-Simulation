#include "State.hpp"
#include <gtest/gtest.h>
#include <memory>

struct StateInitializationTests : public testing::Test
{
    std::unique_ptr<State> default_state = std::make_unique<State>();
};

TEST_F(StateInitializationTests, CorrectConstructionFunctionality_StateIsNormalWhenFirsCreated)
{
    EXPECT_EQ(default_state->getBuildingState(), BuildingState::NORMAL);
    EXPECT_EQ(default_state->getTimeToLive(), InitialTimeToLive::Normal);
}

struct DifferentStatesTests : public testing::Test
{
    std::unique_ptr<State> burning_state = std::make_unique<State>();
    std::unique_ptr<State> ruined_state = std::make_unique<State>();
    DifferentStatesTests()
    {
        burning_state->setBuildingState(BuildingState::BURNING);
        ruined_state->setBuildingState(BuildingState::RUIN);
    }
};

TEST_F(DifferentStatesTests, CorrectStateValues_BurningStateValuesMatchExpected)
{
    EXPECT_EQ(burning_state->getBuildingState(), BuildingState::BURNING);
    EXPECT_EQ(burning_state->getTimeToLive(), InitialTimeToLive::Burning);
}

TEST_F(DifferentStatesTests, CorrectStateValues_RuinedStateValuesMatchExpected)
{
    EXPECT_EQ(ruined_state->getBuildingState(), BuildingState::RUIN);
    EXPECT_EQ(ruined_state->getTimeToLive(), InitialTimeToLive::Ruin);
}

struct StateDecayTests : public testing::Test
{
    std::unique_ptr<State> state = std::make_unique<State>();
    unsigned int initial_time_to_live{ state->getTimeToLive() };
};

TEST_F(StateDecayTests, CorrectStateValues_RuinedStateValuesMatchExpected)
{
    state->doDecay();
    EXPECT_EQ(initial_time_to_live - state->getTimeToLive(), StateConstants::TimeToLiveDecayValue);
}
