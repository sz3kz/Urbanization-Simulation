#pragma once
#include "Disaster.hpp"
#include "Coordinates.hpp"

class Tornado : public Disaster {
    void doEvent(Coordinates coords);
    void doEvent(Coordinates coords, int lifetime);
};
