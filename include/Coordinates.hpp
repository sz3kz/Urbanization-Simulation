#pragma once
/**
 * @brief Represents a position on a two-dimensional board.
 *
 * Coordinates are expressed using integer x and y values.
 */
struct Coordinates
{
    /**
     * @brief Horizontal coordinate.
     */
    int x;

    /**
     * @brief Vertical coordinate.
     */
    int y;

    /**
     * @brief Constructs a coordinate pair.
     *
     * @param x Horizontal coordinate.
     * @param y Vertical coordinate.
     */
    Coordinates(int x, int y)
      : x(x)
      , y(y)
    {
    }

    /**
     * @brief Compares two coordinates for equality.
     *
     * Two coordinates are equal when both their x and y values
     * are identical.
     *
     * @param first First coordinate
     * @param second Second coordinate
     * @return true if both coordinates represent the same position.
     * @return false otherwise.
     */
    friend auto operator==(const Coordinates& first, const Coordinates& second) -> bool;
};

inline auto operator==(const Coordinates& first, const Coordinates& second) -> bool
{
    return first.x == second.x && first.y == second.y;
}