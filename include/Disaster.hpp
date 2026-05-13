#pragma once
#include "RandomEvent.hpp"


class Disaster : public RandomEvent {
    Disaster();
    void doEvent(Coordinates coords);
    void doEvent(Coordinates coords, int severity);
};
