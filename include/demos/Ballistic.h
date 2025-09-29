#pragma once
#include "Shot.h"
#include <memory>

class Ballistic {
public:
    std::unique_ptr<Shot> shot;

    Ballistic(bulletType type);

    void update(double dt);
    cyclone::Vector3 getPosition() const;
    bool isActive() const;
};