#include "CellOccupant.hpp"
#include "House.hpp"
#include <gtest/gtest.h>
#include <random>

/*
TEST(SimulationTests,
     CellOccupant_CorrectConstructionFunctionality_ConstructedCellOccupantHoldsCorrectOccupant)
{
    int value = 100;
    auto myHouse = std::make_unique<House>(value);

    // 2. Transfer ownership to the CellOccupant
    // After this line, 'myDummy' becomes null!
    CellOccupant cell_occupant(std::move(myHouse));
    EXPECT_EQ(cell_occupant.occupant->x, value);
}
*/