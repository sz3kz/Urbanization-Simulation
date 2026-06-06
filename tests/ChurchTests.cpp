#include "Church.hpp"
#include <gtest/gtest.h>

struct ChurchBuildingTypeIdentificationTests : public testing::Test
{
    std::unique_ptr<Building> building = std::make_unique<Church>();
};

TEST_F(ChurchBuildingTypeIdentificationTests,
       CorrectIdentification_BuildingObjectReturnsCorrectBuildingType)
{
    EXPECT_EQ(building->getBuildingType(), BuildingType::CHURCH);
}