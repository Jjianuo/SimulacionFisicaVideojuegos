#pragma once

#include "ForceGenerator.h"
#include "core.hpp"
#include <cmath>

class SpringForce : public ForceGenerator
{
protected:
	double K;
	double restingLength;
	Particle* other;
public:
	SpringForce(double k, double restLen, Particle* p)
		: K(k), restingLength(restLen), other(p) {};

	virtual void updateForce(Particle* p, double t);

	inline void setK(double d) { K = d; }
};