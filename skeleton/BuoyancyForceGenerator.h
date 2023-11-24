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
	double immersed;
public:
	BuoyancyForceGenerator(Particle* p, double h, double v, double d)
		: liquid(p), height(h), volume(v), density(d), immersed(0) { };

	virtual void updateForce(Particle* p, double t);

};

