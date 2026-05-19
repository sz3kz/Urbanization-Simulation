#pragma once
#include "World.hpp"
#include <map>

struct Probability
{
    unsigned long last_updated_at_iteration;
    double value;
};

struct CellProbabilities
{
    std::map<ProbabilityType, Probability> probabilities;
    CellProbabilities();
};