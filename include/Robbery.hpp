#pragma once
#include "Disaster.hpp"
#include "Coordinates.hpp"

class Robbery : public Disaster {

    void doEvent(Coordinates coords);
    void doEvent(Coordinates coords, int severity);//opcjonalnie?
};
