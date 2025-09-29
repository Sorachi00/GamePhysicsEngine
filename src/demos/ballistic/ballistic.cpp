#include "demos/Ballistic.h"

Ballistic::Ballistic(bulletType type) {
    shot = std::make_unique<Shot>();
    switch (type) {
    case Pistol:
        shot->particle.setMass(2.0f); // kg
        shot->particle.setVelocity(cyclone::Vector3(0.0f, 0.0f, 35.0f)); //ms
        shot->particle.setAcceleration(cyclone::Vector3(0.0f, -1.0f, 0.0f));//g'=(1/dS) * g for smoother gravity. This should be -10 if we use real graviy or -0.28 if we correctly applying the formula. S is the velocity
        shot->particle.setDamping(1.0f);
        break;
    }
    shot->particle.setPosition(cyclone::Vector3(0.0f, 1.5f, 0.0f));
    time(&shot->startTime);
    shot->type = type;
    shot->particle.clearAccumulator();
}

void Ballistic::update(double dt) {
    shot->particle.integrate(dt);
    time_t curTime;
    if (shot->particle.getPosition().y < 0.0f ||
        shot->startTime + 5 < time(&curTime) ||
        shot->particle.getPosition().z > 200.0f)
    {
        shot->type = UNUSED;
    }
}

cyclone::Vector3 Ballistic::getPosition() const {
    return shot->particle.getPosition();
}

bool Ballistic::isActive() const {
    return shot->type != UNUSED;
}
