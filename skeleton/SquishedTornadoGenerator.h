#pragma once

#include "ForceGenerator.h"
#include "core.hpp"
#include <cmath>

class SquishedTornadoGenerator : public ForceGenerator
{
protected:
	Vector3 origin;
	double area;
	double K;
	double dragCoef;
	Vector3 linearVel;
	Vector3 angularVel;
public:
	SquishedTornadoGenerator(int k = 3, const Vector3& _origin = { 0.0, 0.0, 0.0 }, const double _area = -1, 
		const Vector3& lvel = { 5.0,5.0,0.0 }, const Vector3& avel = { 5.0,5.0,0.0 })
		: K(k), origin(_origin), area(_area), linearVel(lvel), angularVel(avel) {};

	virtual void updateForce(Particle* p, double t);

	inline void setOrigin(Vector3 o) { origin = o; }
	inline void setArea(double a) { area = a; }
};

