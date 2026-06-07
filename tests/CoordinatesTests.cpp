#include "Coordinates.hpp"
#include <gtest/gtest.h>

struct CoordinatesInitializationTests : public testing::Test
{
    int random_x{ 5 };
    int random_y{ 6 };
};

TEST_F(CoordinatesInitializationTests,
       CorrectConstructionFunctionality_CoordinatesMembersMatchConstructorParameters)
{
    Coordinates coordinates(random_x, random_y);
    EXPECT_EQ(coordinates.x, random_x);
    EXPECT_EQ(coordinates.y, random_y);
}

struct CoordinatesEqualityTests : public testing::Test
{
    int random_x0{ 5 };
    int random_y0{ 6 };
    int random_x1{ 3 };
    int random_y1{ 9 };
};

TEST_F(
  CoordinatesEqualityTests,
  EqualCoordinatesHandling_OverloadedCompareOperatorReturnsTrueForCoordinatesOfMatchingDataMemberValues)
{
    Coordinates coordinates1(random_x0, random_y0);
    Coordinates coordinates2(random_x0, random_y0);
    EXPECT_EQ((coordinates1 == coordinates2), true);
}

TEST_F(
  CoordinatesEqualityTests,
  UnequalCoordinatesHandling_OverloadedCompareOperatorReturnsFalseForCoordinatesOfVaryingDataMemberValues)
{
    Coordinates coordinates1(random_x1, random_y1);
    Coordinates coordinates2(random_x0, random_y0);
    EXPECT_EQ((coordinates1 == coordinates2), false);
}