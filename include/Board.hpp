#pragma once
#include "Coordinates.hpp"
#include <vector>

template<typename T>
class Board
{
    unsigned int width;
    unsigned int height;
    std::vector<T> contents;

  public:
    Board(unsigned int width, unsigned int height)
      : width(width)
      , height(height)
      , contents(width * height) {};
    auto calculateIndexFromCoordinates(Coordinates const& coordinates) const -> unsigned int;
    auto getWidth() const -> unsigned int;
    auto getHeight() const -> unsigned int;
    /*BuildingType getCellBuildingType(Coordinates const& coordinates);*/
    /*auto getCellOccupant(Coordinates coords) -> CellOccupant *;*/
    /*void applyProbability(Coordinates const& coordinates); */
};

template<typename T>
auto Board<T>::calculateIndexFromCoordinates(Coordinates const& coordinates) const -> unsigned int
{
    return coordinates.y * width + coordinates.x;
}

template<typename T>
auto Board<T>::getWidth() const -> unsigned int
{
    return width;
}

template<typename T>
auto Board<T>::getHeight() const -> unsigned int
{
    return height;
}
