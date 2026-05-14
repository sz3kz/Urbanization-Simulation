#include "Board.hpp"
#include <gtest/gtest.h>
#include <random>

TEST(SimulationTests,
     Board_CorrectConstructionFunctionalityy_MembersMatchConstructorParameters)
{
    std::random_device my_random_device;
    std::mt19937 my_generator(my_random_device());
    std::uniform_int_distribution<> distr(1, 100);

    int randomized_width = distr(my_generator);
    int randomized_height = distr(my_generator);

    Board<int> board(randomized_width, randomized_height);
    EXPECT_EQ(board.getWidth(), randomized_width);
    EXPECT_EQ(board.getHeight(), randomized_height);
}