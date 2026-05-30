#include "../include/World.hpp"
#include "Simulation.hpp"
#include "World.hpp"

#include <iostream>
#include <locale>

void usage(const char* name)
{
    std::cout << "Usage: ./" << name << " <width> <height> <random-seed>\n";
    return;
}

auto main(int argc, char* argv[]) -> int
{
    if (argc != static_cast<int>(ArgumentType::ARGS))
    {
        usage(argv[static_cast<int>(ArgumentType::EXEC_NAME)]);
        return 1;
    }
    // here loading 3 first arguments - numbers
    int width, height, random_seed;
    try
    {

        width = std::stoi(argv[static_cast<int>(ArgumentType::WIDTH)]);

        height = std::stoi(argv[static_cast<int>(ArgumentType::HEIGHT)]);

        random_seed = std::stoi(argv[static_cast<int>(ArgumentType::SEED)]);
    }
    catch (std::invalid_argument& e)
    {
        usage(argv[static_cast<int>(ArgumentType::EXEC_NAME)]);
    }
    if (width < 1 || height < 1 || random_seed < 1)
    {
        usage(argv[static_cast<int>(ArgumentType::EXEC_NAME)]);
        return 1;
    }

    std::locale::global(std::locale(""));
    std::cout.imbue(std::locale());
    Simulation simulation(width, height, random_seed);
    std::cout << "Started simulation:" << '\n';
    simulation.run();
    return 0;
}