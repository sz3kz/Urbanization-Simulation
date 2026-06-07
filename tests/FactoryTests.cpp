#include "Factory.hpp"
#include <gtest/gtest.h>

struct FactoryBuildingTypeIdentificationTests : public testing::Test
{
    std::unique_ptr<Building> building = std::make_unique<Factory>();
};

TEST_F(FactoryBuildingTypeIdentificationTests,
       CorrectIdentification_BuildingObjectReturnsCorrectBuildingType)
{
    EXPECT_EQ(building->getBuildingType(), BuildingType::FACTORY);
}