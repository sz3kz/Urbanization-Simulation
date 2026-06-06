#include "CellOccupant.hpp"
#include "House.hpp"
#include <gtest/gtest.h>

struct CelloccupantInitializationTests : public testing::Test
{
    CellOccupant default_cell;
    std::unique_ptr<Building> building = std::make_unique<House>();
};

TEST_F(CelloccupantInitializationTests,
       CorrectConstructionFunctionality_CelloccupantConstructionCreatesEmptyCell)
{
    EXPECT_EQ(default_cell.occupant, nullptr);
}

TEST_F(
  CelloccupantInitializationTests,
  CorrectConstructionFunctionality_CelloccupantParameteredConstructionCreatesCellWithAutomaticBuildingAcquisition)
{
    Building const* ptr = building.get();
    CellOccupant cell(std::move(building));
    EXPECT_EQ(cell.occupant.get() == ptr, true);
}

struct OccupiedCellTests : public testing::Test
{
    std::unique_ptr<Building> building = std::make_unique<House>();
    CellOccupant cell{ std::move(building) };
};

TEST_F(OccupiedCellTests, OccupantChecking_OccupiedCellReportsBeingOccupied)
{
    EXPECT_EQ(cell.checkCellEmpty(), false);
}

TEST_F(OccupiedCellTests, OccupatantDeletion_OccupiedCellReportsNullptrToOccupantAfterReleasingIt)
{
    cell.release();
    EXPECT_EQ(cell.occupant, nullptr);
}

TEST_F(OccupiedCellTests, OccupantChecking_OccupiedCellReportsBeingEmptyAfterReleasing)
{
    cell.release();
    EXPECT_EQ(cell.checkCellEmpty(), true);
}
TEST_F(OccupiedCellTests, OccupantChecking_OccupiedCellHoldsCorrectPointer)
{
    Building const* ptr = cell.getBuilding();
    auto uptr = cell.release();
    EXPECT_EQ(ptr == uptr.get(), true);
}

TEST_F(OccupiedCellTests, OccupantTransformation_NormalOccupantTransformsIntoRuinedOne)
{
    cell.transformState();
    EXPECT_EQ(cell.occupant->getBuildingState(), BuildingState::RUIN);
}

TEST_F(OccupiedCellTests, OccupantTransformation_BurningOccupantTransformsIntoRuinedOne)
{
    cell.occupant->setBuildingState(BuildingState::BURNING);
    cell.transformState();
    EXPECT_EQ(cell.occupant->getBuildingState(), BuildingState::RUIN);
}

TEST_F(OccupiedCellTests, OccupantTransformation_RuinedOccupantTransformationLeavesCellEmpty)
{
    cell.occupant->setBuildingState(BuildingState::RUIN);
    cell.transformState();
    EXPECT_EQ(cell.checkCellEmpty(), true);
}