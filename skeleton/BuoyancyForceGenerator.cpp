#include "BuoyancyForceGenerator.h"

void BuoyancyForceGenerator::updateForce(Particle* p, double t)
{
	if (fabs(p->getInvMass()) < 1e-10 || !active) return;

	const float h = p->getPose().p.y;
	const float h0 = liquid->getPose().p.y;

	Vector3 f(0, 0, 0);
	Vector3 f2(0, 0, 0);
	float v = 0;
	if (h - h0 > height * 0.5) {
		immersed = 0.0;
		frictionCoef = 0.01;
	}
	else {
		frictionCoef = 0.5;
		if (h0 - h > height * 0.5) 
			immersed = 1.0;
		else 
			immersed = (h0 - h) / height + 0.5;
	}

	f.y = density * volume * immersed * gravity;
	f2.y = -1 * frictionCoef * normal * (p->getVelocity() + f).normalize();

	p->addForce(f);
	p->addForce(f2);
}
