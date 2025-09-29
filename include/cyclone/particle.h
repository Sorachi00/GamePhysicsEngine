//A particle is the simplest object that can be simulated in the physics system. It has a position but no orientation, so we can't tell where is pointing. 

#include "core.h"
namespace cyclone {
	class Particle {
	protected:
		Vector3 position;

		Vector3 velocity;

		Vector3 acceleration;

		real damping; //Holds the amount of damping applied to linear motion. Damping is required to remove energy added through numerical inestability in the integrator

		real inverseMass; //is better to have inverse mass to manage immovible objects 1/m


	public:
		void setMass(real value);
		void setVelocity(Vector3 value);
		void setAcceleration(Vector3 value);
		void setDamping(real value);
		void setPosition(Vector3 value);
		void clearAccumulator();
		Vector3 getPosition();
		void integrate(real duration);


	};
	
}
