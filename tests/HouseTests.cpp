#include "House.hpp"
#include <gtest/gtest.h>

struct HouseBuildingTypeIdentificationTests : public testing::Test
{
    std::unique_ptr<Building> building = std::make_unique<House>();
};

TEST_F(HouseBuildingTypeIdentificationTests,
       CorrectIdentification_BuildingObjectReturnsCorrectBuildingType)
{
    EXPECT_EQ(building->getBuildingType(), BuildingType::HOUSE);
}