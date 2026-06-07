#include "Board.hpp"
#include <gtest/gtest.h>

struct BoardTests : public testing::Test
{
    unsigned int width{ 67 };
    unsigned int height{ 420 };
    Board<int> board;
    BoardTests()
      : board(width, height)
    {
    }
};

TEST_F(BoardTests, CorrectConstructionFunctionality_MembersMatchConstructorParameters)
{
    EXPECT_EQ(board.getWidth(), width);
    EXPECT_EQ(board.getHeight(), height);
}

struct BoardCoordinateValidationTests : public testing::Test
{
    unsigned int width{ 2 };
    unsigned int height{ 2 };
    Board<int> board;
    int valid_x{ 1 };
    int valid_y{ 0 };
    Coordinates valid_coordinates;
    int invalid_x{ -1 };
    int invalid_y{ 2 };
    Coordinates invalid_coordinates;
    BoardCoordinateValidationTests()
      : board(width, height)
      , valid_coordinates(valid_x, valid_y)
      , invalid_coordinates(invalid_x, invalid_y) {};
};

TEST_F(BoardCoordinateValidationTests, ValidCoordinates_BoardDeemsValid)
{
    EXPECT_EQ(board.checkCellExistsAtCoordinates(valid_coordinates), true);
}

TEST_F(BoardCoordinateValidationTests, InvalidCoordinates_BoardDeemsInvalid)
{
    EXPECT_EQ(board.checkCellExistsAtCoordinates(invalid_coordinates), false);
}

struct BoardCoordinateToIndexTests : public testing::Test
{
    unsigned int width{ 2 };
    unsigned int height{ 2 };
    Board<int> board;
    int first_row_x{ 1 };
    int first_row_y{ 0 };
    Coordinates first_row_coordinates;
    int second_row_x{ 1 };
    int second_row_y{ 1 };
    Coordinates second_row_coordinates;
    BoardCoordinateToIndexTests()
      : board(width, height)
      , first_row_coordinates(first_row_x, first_row_y)
      , second_row_coordinates(second_row_x, second_row_y) {};
};

TEST_F(BoardCoordinateToIndexTests, FirstRowCoordinates_ProducesExpectedIndex)
{
    EXPECT_EQ(board.calculateIndexFromCoordinates(first_row_coordinates), first_row_x);
}

TEST_F(BoardCoordinateToIndexTests, SecondRowCoordinates_ProducesExpectedIndex)
{
    EXPECT_EQ(board.calculateIndexFromCoordinates(second_row_coordinates), second_row_x + width);
}
