#pragma once

#include "ForceGenerator.h"
#include "core.hpp"
#include <cmath>

class CentripetalForce : public ForceGenerator
{
protected:
	Vector3 origin;
	Vector3 vel;
	double area;
	double K;
	double r;
public:
	CentripetalForce(int k = 3, const Vector3& _origin = { 0.0, 0.0, 0.0 }, const Vector3 & _velocity = { 0.0, 0.0, 0.0 }, 
		const double _area = -1, const double rad = 20)
		: K(k), origin(_origin), vel(_velocity), area(_area), r(rad) {};

	virtual void updateForce(Particle* p, double t);

	inline void setOrigin(Vector3 o) { origin = o; }
	inline void setArea(double a) { area = a; }
};
