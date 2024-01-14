#pragma once

#include "WindGenerator.h"

class SquishedTornadoGenerator : public WindGenerator
{
protected:
	Vector3 _gravity;
	double K;
public:
	SquishedTornadoGenerator(double _K, const Vector3& _origin = { 0.0, 0.0, 0.0 }, const double _area = -1, const Vector3& vel = { 10.0,10.0,10.0 })
		: WindGenerator(_origin, _area, vel, 0.3, 0.5, 1.225, true), K(_K) {};

	virtual void updateForce(Particle* p, double t);
};
