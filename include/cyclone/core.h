#pragma once
#include "precision.h"

namespace cyclone {
	class Vector3
	{
	public:
		real x;
		real y;
		real z;

	private:
		real pad; //Four floating points values sit more cleanly in memory than 3, so this will maybe speed up

	public:
		Vector3() : x(0), y(0), z(0) {}

		Vector3(const real x, const real y, const real z) : x(x), y(y), z(z) {}

		void invert() {
			x = -x;
			y = -y;
			z = -z;
		}

		real magnitude() const {
			return real_sqrt(x * x + y * y + z * z);
		}

		real squareMagnitude() const { //A faster way for when we do not need exact magnituded for example to see which is grater.
			return x * x + y * y + z * z;
		}

		void normalize() {
			real l = magnitude();
			if (l > 0) {
				(*this) *= ((real)1) / l;
			}
		}

		void operator*=(const real value) {
			x *= value;
			y *= value;
			z *= value;
		}

		Vector3 operator*(const real value) const {
			return Vector3(x * value, y * value, z * value);
		}

		void operator+=(const Vector3& v) {
			x += v.x;
			y += v.y;
			z += v.z;
		}

		Vector3 operator+(const Vector3& v) const {
			return Vector3(x + v.x, y + v.y, z + v.z);
		}

		void operator-=(const Vector3& v) {
			x -= v.x;
			y -= v.y;
			z -= v.z;
		}

		Vector3 operator-(const Vector3& v) const {
			return Vector3(x - v.x, y - v.y, z - v.z);
		}

		void addScaledVector(const Vector3& v, real scale) {
			x += v.x * scale;
			y += v.y * scale;
			z += v.z * scale;
		}

		Vector3 componentProduct(const Vector3& v) const {
			return Vector3(x * v.x, y * v.y, z * v.z);
		}

		void componentProductUpdate(const Vector3& v) {
			x *= v.x;
			y *= v.y;
			z *= v.z;
		}

		float scalarProduct(const Vector3& v) const {
			return x * v.x + y * v.y + z * v.z;
		}

		real operator*(const Vector3& v) const {
			return x * v.x + y * v.y + z * v.z;
		}

		Vector3 vectorProduct(const Vector3& v) const {
			return Vector3(
				y * v.z - z * v.y,
				z * v.x - x * v.z,
				x * v.y - y * v.x
			);
		}

		//***vector product is not commutative a X b = -b X a. incorrect order can cause objects being sucket into each other or by bobbing in and out of supposedly solid surfaces***

		void operator%=(const Vector3& v) { //overloading % just because seems like a cross
			(*this) = vectorProduct(v);
		}

		Vector3 operator%(const Vector3& v) const {
			return Vector3(
				y * v.z - z * v.y,
				z * v.x - x * v.z,
				x * v.y - y * v.x
			);
		}

		void makeOrthonormalBasis(Vector3* a, Vector3* b, Vector3* c) { //generate orthonormal basis with 2 fixed axes. Later I will probably need one for only one fixed axis. Note: this is designed for right-handed systems
			a->normalize();
			(*c) = (*a) % (*b);
			if (c->squareMagnitude() == 0.0) return;
			c->normalize();
			(*b) = (*c) % (*a);
		}
	};
}