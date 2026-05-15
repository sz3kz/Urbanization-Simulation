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
    [[nodiscard]]
    auto checkCellExistsAtCoordinates(Coordinates const& coordinates) const -> bool;
    [[nodiscard]]
    auto calculateIndexFromCoordinates(Coordinates const& coordinates) const -> unsigned int;
    [[nodiscard]]
    auto getWidth() const -> unsigned int;
    [[nodiscard]]
    auto getHeight() const -> unsigned int;
    void setContentsValueAtCoordinates(Coordinates const& coordinates, T value);
    /*BuildingType getCellBuildingType(Coordinates const& coordinates);*/
    /*auto getCellOccupant(Coordinates coords) -> CellOccupant *;*/
    /*void applyProbability(Coordinates const& coordinates); */
};

template<typename T>
auto Board<T>::checkCellExistsAtCoordinates(Coordinates const& coordinates) const -> bool
{
    if (coordinates.x < 0 || coordinates.x >= width) return false;
    if (coordinates.y < 0 || coordinates.y >= height) return false;
    return true;
}

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

template<typename T>
void Board<T>::setContentsValueAtCoordinates(Coordinates const& coordinates, T value)
{
    unsigned int index = calculateIndexFromCoordinates(coordinates);
    contents.at(index) = value;
}
