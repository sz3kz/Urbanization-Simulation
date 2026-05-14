#include "Coordinates.hpp"
#include <gtest/gtest.h>
#include <random>

TEST(SimulationTests,
     Coordinates_CorrectConstructionFunctionalityy_CoordinatesMembersMatchConstructorParameters)
{
    std::random_device my_random_device;
    std::mt19937 my_generator(my_random_device());
    std::uniform_int_distribution<> distr(1, 100);

    int randomized_x = distr(my_generator);
    int randomized_y = distr(my_generator);

    struct Coordinates coordinates(randomized_x, randomized_y);
    EXPECT_EQ(coordinates.x, randomized_x);
    EXPECT_EQ(coordinates.y, randomized_y);
}