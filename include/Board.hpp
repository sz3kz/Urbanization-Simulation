#pragma once
#include "CellOccupant.hpp"
#include "Coordinates.hpp"
#include "World.hpp"
#include <vector>

template<typename T>
class Board
{
  private:
    unsigned int width;
    unsigned int height;
    std::vector<T> contents;

  public:
    Board(unsigned int width, unsigned int height);
    auto calculateIndexFromCoordinates(Coordinates const& coordinates)-> unsigned int;
    auto checkCellExistsAtCoordinates(Coordinates const& coordinates) -> bool;
    auto checkCellEmptyAtCoordinates(Coordinates const& coordinates) -> bool;
    /*BuildingType getCellBuildingType(Coordinates const& coordinates);*/
    /*auto getCellOccupant(Coordinates coords) -> CellOccupant *;*/
    /*void applyProbability(Coordinates const& coordinates); */
};

template<typename T>
Board<T>::Board(unsigned int width, unsigned int height)
{
    this->width = width;
    this->height = height;
    contents.resize(width * height);
}

template<typename T>
auto Board<T>::calculateIndexFromCoordinates(Coordinates const& coordinates) -> unsigned int
{
}

template<typename T>
auto Board<T>::checkCellExistsAtCoordinates(Coordinates const& coordinates)-> bool
{
}

template<typename T>
auto Board<T>::checkCellEmptyAtCoordinates(Coordinates const& coordinates) -> bool
{
}

Board(Coordinates const&);
	auto getCellOccupant(Coordinates coords) -> CellOccupant*;
	protected:
	void GenerateBoard();

	Coordinates size;
	CellOccupant*** board;
};