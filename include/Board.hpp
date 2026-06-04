#pragma once
#include "Coordinates.hpp"
#include <utility>
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
    auto getCellAtCoordinates(Coordinates const& coordinates) const -> const T&;
    [[nodiscard]]
    auto getCellAtCoordinates(Coordinates const& coordinates) -> T&;
    [[nodiscard]]
    auto getWidth() const -> unsigned int;
    [[nodiscard]]
    auto getHeight() const -> unsigned int;
};

template<typename T>
auto Board<T>::checkCellExistsAtCoordinates(Coordinates const& coordinates) const -> bool
{
    if (coordinates.x < 0 || std::cmp_greater_equal(coordinates.x, width)) return false;
    if (coordinates.y < 0 || std::cmp_greater_equal(coordinates.y, height)) return false;
    return true;
}

template<typename T>
auto Board<T>::getCellAtCoordinates(Coordinates const& coordinates) const -> const T&
{
    return this->contents.at(calculateIndexFromCoordinates(coordinates));
}

template<typename T>
auto Board<T>::getCellAtCoordinates(Coordinates const& coordinates) -> T&
{
    return this->contents.at(calculateIndexFromCoordinates(coordinates));
}

template<typename T>
auto Board<T>::calculateIndexFromCoordinates(Coordinates const& coordinates) const -> unsigned int
{
    return (coordinates.y * width) + coordinates.x;
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