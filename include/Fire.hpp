#pragma once
#include "Disaster.hpp"


class Fire : public Disaster {
    Fire();
    void doEvent(Coordinates coords);
    void doEvent(Coordinates coords, int severity);
};
