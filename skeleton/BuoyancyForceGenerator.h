#pragma once

#include "ForceGenerator.h"
#include "core.hpp"

class BuoyancyForceGenerator : public ForceGenerator
{
protected:
	Particle* liquid;
	double height;
	double volume;
	double density;
	double gravity;
	double immersed;
	double frictionCoef;
	double normal;
public:
	BuoyancyForceGenerator(Particle* p, double h, double v, double d, double g, double fc = 0.01, double n = 1)
		: liquid(p), height(h), volume(v), density(d), gravity(g), frictionCoef(fc), normal(n), immersed(0) { };

	virtual void updateForce(Particle* p, double t);

};

