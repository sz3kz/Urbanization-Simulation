#include "Simulation.hpp"
#include "World.hpp"
#include <iostream>
#include <locale>

auto main() -> int
{
    std::locale::global(std::locale(""));
    std::cout.imbue(std::locale());
    Simulation simulation(50, 50, 1);
    std::cout << "Started simulation:" << '\n';
    simulation.run();
    return 0;
}