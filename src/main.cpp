#include "Simulation.hpp"
#include "World.hpp"
#include <iostream>
#include <locale>

void usage()
{
    std::cout <<"Usage: ./simulation <width> <height> <random-seed>\n";
    return;
}

auto read(const char* table) -> int
{
    int length = 0;
    while (table[length] != 0)
    {
            length++;
    }
    int m=1, value = 0;
    for (int i = length-1; i >= 0; i--)
    {
        if (table[i] - '0'<0 || table[i] - '0' > 9)
        {
            usage();
            return -1;
        }
        value = value + (table[i]-'0')*m;
        m = m *10;
    }
    return value;
}
auto main(int argc, char *argv[]) -> int
{
    if (argc != 4)
    {
        usage();
        return 1;
    }

    int width, height, random_seed;

    width = read(argv[1]);
    height = read(argv[2]);
    random_seed = read(argv[3]);

    if (width < 1 || height < 1 || random_seed < 1)
    {
        return 1;
    }

    std::locale::global(std::locale(""));
    std::cout.imbue(std::locale());
    Simulation simulation(width, height, random_seed);
    std::cout << "Started simulation:" << '\n';
    simulation.run();
    return 0;
}