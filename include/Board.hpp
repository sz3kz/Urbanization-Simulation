#pragma once
#include "Coordinates.hpp"
#include <utility>
#include <vector>

/**
 * @brief Represents a two-dimensional board storing elements of template type.
 *
 * The contents are stored in a classic std::vector, we implemented Coordinates
 * handling to be more human-friendly.
 *
 * @tparam T template to modularize vector content, allowing for later code recycling.
 */
template<typename T>
class Board
{
    unsigned int width;      ///< Width of specific board object
    unsigned int height;     ///< Height of specific board object
    std::vector<T> contents; ///< The actual vector

  public:
    /**
     * @brief Parametered Constructor
     *
     * All cells are default-initialized to be empty, be it CellOccupant or
     * CellProbabilities.
     *
     * @param width Width of specific board object
     * @param height Height of specific board object
     */
    Board(unsigned int width, unsigned int height)
      : width(width)
      , height(height)
      , contents(width * height)
    {
    }

    /**
     * @brief Checks if given coordinates are sus or nah.
     *
     * @param coordinates Coordinates to validate
     * @return true if the coordinates are inside the board boundaries
     * @return false otherwise
     */
    [[nodiscard]]
    auto checkCellExistsAtCoordinates(Coordinates const& coordinates) const -> bool;

    /**
     * @brief Links (converts) a coordinate object to the index of the cell it's
     * referring to.
     *
     * @param coordinates Coordinates to convert
     * @return Corresponding index in the vector
     *
     * @warning Does not check if Coordinates correspond to valid cell on board.
     * Will not error handle.
     */
    [[nodiscard]]
    auto calculateIndexFromCoordinates(Coordinates const& coordinates) const -> unsigned int;

    /**
     * @brief Classic getter to a const reference cell on the board
     *
     * @param coordinates Coordinates of interest
     * @return Const reference to the cell
     *
     * @throws std::out_of_range (if calculated index is bogus)
     */
    [[nodiscard]]
    auto getCellAtCoordinates(Coordinates const& coordinates) const -> const T&;

    /**
     * @brief Classic getter to a modifiable reference of cell on the board.
     *
     * @param coordinates Coordinates of the requested cell
     * @return Reference to the stored value
     *
     * @throws std::out_of_range (if calculated index is bogus)
     */
    [[nodiscard]]
    auto getCellAtCoordinates(Coordinates const& coordinates) -> T&;

    /**
     * @brief Classic getter to the width of the specific board.
     *
     * @return Width
     */
    [[nodiscard]]
    auto getWidth() const -> unsigned int;

    /**
     * @brief Classic getter to the height of the specific board.
     *
     * @return Height
     */
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