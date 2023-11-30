#include "BuoyancyForceGenerator.h"

void BuoyancyForceGenerator::updateForce(Particle* p, double t)
{
	if (fabs(p->getInvMass()) < 1e-10) return;

	const float h = p->getPose().p.y;
	const float h0 = liquid->getPose().p.y;

	Vector3 f(0, 0, 0);
	float v = 0;
	if (h - h0 > height * 0.5) 
		immersed = 0.0;
	else {
		v = -1 * frictionCoef * normal * p->getVelocity().normalize();
		if (h0 - h > height * 0.5) 
			immersed = 1.0;
		else 
			immersed = (h0 - h) / height + 0.5;
	}

	f.y = density * volume * immersed * gravity + v;

	p->addForce(f);
}
