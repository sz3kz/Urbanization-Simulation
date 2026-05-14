#include "CellOccupant.hpp"
#include <gtest/gtest.h>
#include <random>

TEST(SimulationTests,
     CellOccupant_CorrectConstructionFunctionalityy_ConstructedCellOccupantHoldsCorrectOccupant)
{
    int value = 100;
    auto myDummy = std::make_unique<Dummy>(value);

    // 2. Transfer ownership to the CellOccupant
    // After this line, 'myDummy' becomes null!
    CellOccupant cell_occupant(std::move(myDummy));
    EXPECT_EQ(cell_occupant.occupant->x, value);
}