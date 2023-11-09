#pragma once

#include "ForceGenerator.h"
#include "core.hpp"
#include <cmath>

const double PI = 3.14159265358979323846;

class WindGenerator : public ForceGenerator
{
protected:
	Vector3 origin;
	double area;
	double k1, k2;
	double dragCoef;
	double airDensity;
	Vector3 windVel;
public:
	WindGenerator(const Vector3& _origin = {0.0, 0.0, 0.0}, const double _area = 25, const Vector3& vel = {5.0,5.0,5.0})
		: origin(_origin), area(_area), k1(0.3), dragCoef(0.5), airDensity(1.225), windVel(vel) {};

	virtual void updateForce(Particle* p, double t);

	inline void setOrigin(Vector3 o) { origin = o; }
	inline void setArea(double a) { area = a; }
};

