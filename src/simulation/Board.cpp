#include "Board.hpp"
Board::Board(Coordinates const& s) : size(s)
{
    GenerateBoard();
}

void Board::GenerateBoard()
{
    board = new CellOccupant**[size.getX()];
    for(int i =0;i<size.getX();i++)
    {
        board[i] = new CellOccupant*[size.getY()];
        for (int j=0;j<size.getY();j++)
        {
            board[i][j]= nullptr;
        }
    }
}