#pragma once

#include "WindGenerator.h"
#include "core.hpp"

class TornadoGenerator : public WindGenerator
{
protected:
	Vector3 _gravity;
	int K;
public:
	TornadoGenerator(const Vector3& _origin = { 0.0, 0.0, 0.0 }, const double _area = 25, const Vector3& vel = { 5.0,5.0,5.0 }) 
		: WindGenerator(_origin, _area, vel), K(5) {};

	virtual void updateForce(Particle* p, double t);
};