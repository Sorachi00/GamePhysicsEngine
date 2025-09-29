#include <iostream>
#include "include/cyclone/core.h"
#include <cyclone/particle.h>
#include <ctime>
#include <memory>
#include <thread>
#include <chrono>
enum bulletType {
	Pistol,
	UNUSED
};

class Shot {
public:
	cyclone::Particle particle;
	bulletType type;
	time_t startTime;
};

class ballistic {
public:
	std::unique_ptr<Shot> shot;

	ballistic(bulletType type) {
		shot = std::make_unique<Shot>();
		switch (type) {
		case Pistol:
			shot->particle.setMass(2.0f); //kg
			cyclone::Vector3 vel(0.0f, 0.0f, 35.0f);//35ms
			shot->particle.setVelocity(vel);
			cyclone::Vector3 acc(0.0f, -1.0f, 0.0f); //g'=(1/dS) * g for smoother gravity. This should be -10 if we use real graviy or -0.28 if we correctly applying the formula. S is the velocity
			shot->particle.setAcceleration(acc);
			shot->particle.setDamping(1.0f);
			break;
		}
		cyclone::Vector3 pos(0.0f, 1.5f, 0.0f);
		shot->particle.setPosition(pos);
		time(&shot->startTime);
		shot->type = type;

		shot->particle.clearAccumulator();
	}

	void update(double dt) {
		shot->particle.integrate(dt);
		time_t curTime;
		if (shot->particle.getPosition().y < 0.0f ||
			shot->startTime + 5 < time(&curTime)||
			shot->particle.getPosition().z > 200.0f)
		{

			shot->type = UNUSED;
		}
	}

	cyclone::Vector3 getPosition() const {
		return shot->particle.getPosition();
	}

	bool isActive() const {
		return shot->type != UNUSED;
	}
};

int main()
{
	ballistic b(Pistol);

	float time = 0;
	while(b.isActive()) { //pseudo 60fps simulation
		b.update(0.016);
		cyclone::Vector3 pos = b.getPosition();
		time += 0.016;
		std::cout << "t=" << time
			<< "s -> Pos("
			<< pos.x << ", " << pos.y << ", " << pos.z << ")\n";
		if (!b.isActive()) {
			std::cout << "El proyectil dejó de estar activo.\n";
			break;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	}
}
