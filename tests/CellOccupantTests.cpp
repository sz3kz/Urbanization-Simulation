#include "CellOccupant.hpp"
#include "House.hpp"
#include <gtest/gtest.h>

struct CelloccupantInitializationTests : public testing::Test
{
    CellOccupant default_cell;
};

TEST_F(CelloccupantInitializationTests,
       CorrectConstructionFunctionality_CelloccupantConstructionCreatesEmptyCell)
{
    EXPECT_EQ(default_cell.checkCellEmpty(), true);
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