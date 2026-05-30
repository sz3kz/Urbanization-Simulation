#pragma once

struct Coordinates
{
    int x;
    int y;
    Coordinates(int x, int y)
      : x(x)
      , y(y) {};
    friend auto operator==(const Coordinates& first, const Coordinates& second) -> bool;
};

inline auto operator==(const Coordinates& first, const Coordinates& second) -> bool
{
    return first.x == second.x && first.y == second.y;
}
