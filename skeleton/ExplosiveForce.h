#pragma once

#include "ForceGenerator.h"
#include "core.hpp"

class ExplosiveForce : public ForceGenerator
{
protected:
	Vector3 origin;
	double area;
	double K;
	double dur;

	Vector3 force;
public:
	ExplosiveForce(const Vector3& _origin = { 0.0, 0.0, 0.0 }, const double p = 1000, const double _area = 25, const double d = 1)
		: origin(_origin), area(_area), K(p), dur(d) {
		_duration = d;
	};

	virtual void updateForce(Particle* p, double t);

	inline void setOrigin(Vector3 o) { origin = o; }
	inline void setArea(double a) { area = a; }
};

