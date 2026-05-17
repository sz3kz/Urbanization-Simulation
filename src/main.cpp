#include "Simulation.hpp"
#include <iostream>
#include <locale>

int main()
{
    std::locale::global(std::locale(""));
    std::cout.imbue(std::locale());
    Simulation simulation(10, 10, 1);
    std::cout << "Started simulation:" << '\n';
    simulation.run();
    return 0;
}