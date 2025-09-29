#pragma once
#include "cyclone/core.h"
#include <cyclone/particle.h>
#include <ctime>

enum bulletType {
    Pistol,
    UNUSED
};

struct Shot {
    cyclone::Particle particle;
    bulletType type;
    time_t startTime;
};