#include "Firestation.hpp"
#include <gtest/gtest.h>

struct FirestationBuildingTypeIdentificationTests : public testing::Test
{
    std::unique_ptr<Building> building = std::make_unique<Firestation>();
};

TEST_F(FirestationBuildingTypeIdentificationTests,
       CorrectIdentification_BuildingObjectReturnsCorrectBuildingType)
{
    EXPECT_EQ(building->getBuildingType(), BuildingType::FIRESTATION);
}