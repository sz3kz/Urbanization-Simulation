#pragma once
#include "Disaster.hpp"
#include "Coordinates.hpp"

class Robbery : public Disaster {
    Robbery();
    void doEvent(Coordinates coords);
    void doEvent(Coordinates coords, int severity);//opcjonalnie?
};
