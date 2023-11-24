#pragma once
#include "SpringForce.h"

class ElasticBandForce : public SpringForce
{
public:
	ElasticBandForce(double k, double restLen, Particle* p);
	virtual void updateForce(Particle* p, double t);
};

