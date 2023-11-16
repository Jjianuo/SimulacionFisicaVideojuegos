#pragma once

#include "WindGenerator.h"
#include "core.hpp"

class TornadoGenerator : public WindGenerator
{
protected:
	Vector3 _gravity;
	double K;
public:
	TornadoGenerator(double _K, const Vector3& _origin = { 0.0, 0.0, 0.0 }, const double _area = -1, const Vector3& vel = { 10.0,10.0,10.0 })
		: WindGenerator(_origin, _area, vel), K(_K) {};

	virtual void updateForce(Particle* p, double t);
};