#include <assert.h>
#include <cyclone/particle.h>

using namespace cyclone;


void Particle::integrate(real duration) {
	//We don't integrate things with infinite mass
	if (inverseMass <= 0.0f) return;

	assert(duration > 0);

	//Update linear position
	position.addScaledVector(velocity, duration);

	//Work out the acceleration from the force
	Vector3 resultingAcc = acceleration;

	//Update linear velocity from acceleration
	velocity.addScaledVector(resultingAcc, duration);

	//Impose drag
	velocity *= real_pow(damping, duration);

	//Clear the forces
	clearAccumulator();
}


void Particle::clearAccumulator() {
	return;
}

void Particle::setMass(real value)
{
	inverseMass = 1 / value;
}

void Particle::setVelocity(Vector3 value)
{
	velocity = value;
}

void Particle::setAcceleration(Vector3 value)
{
	acceleration = value;
}

void Particle::setPosition(Vector3 value)
{
	position = value;
}


void Particle::setDamping(real value)
{
	damping = value;
}

Vector3 Particle::getPosition() {
	return position;
}

