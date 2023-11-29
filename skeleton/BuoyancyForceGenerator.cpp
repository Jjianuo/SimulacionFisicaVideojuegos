#include "BuoyancyForceGenerator.h"

void BuoyancyForceGenerator::updateForce(Particle* p, double t)
{
	if (fabs(p->getInvMass()) < 1e-10) return;

	const float h = p->getPose().p.y;
	const float h0 = liquid->getPose().p.y;

	Vector3 f(0, 0, 0);
	if (h - h0 > height * 0.5) immersed = 0.0;
	else if (h0 - h > height * 0.5) immersed = 1.0;
	else immersed = (h0 - h) / height + 0.5;

	Vector3 velocity = p->getVelocity();
	f.y = density * volume * immersed * 9.8;
	f -= frictionCoef * normal * velocity;

	p->addForce(f);
}
