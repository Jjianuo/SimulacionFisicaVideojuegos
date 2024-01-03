#include "ElasticBandForce.h"

ElasticBandForce::ElasticBandForce(double k, double restLen, Particle* p) : SpringForce(k, restLen, p)
{
}

void ElasticBandForce::updateForce(Particle* p, double t)
{
	if (fabs(p->getInvMass()) < 1e-10 || !active)
		return;

	Vector3 rel_pos = other->getPose().p - p->getPose().p;
	if (rel_pos.magnitude() > restingLength) {
		SpringForce::updateForce(p, t);
	}
}
