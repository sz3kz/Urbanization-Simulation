#include "Shop.hpp"
#include <gtest/gtest.h>

struct ShopBuildingTypeIdentificationTests : public testing::Test
{
    std::unique_ptr<Building> building = std::make_unique<Shop>();
};

TEST_F(ShopBuildingTypeIdentificationTests,
       CorrectIdentification_BuildingObjectReturnsCorrectBuildingType)
{
    EXPECT_EQ(building->getBuildingType(), BuildingType::SHOP);
}
