#include "TornadoGenerator.h"

void TornadoGenerator::updateForce(Particle* p, double t)
{
	const Vector3 aux = p->getPose().p;
	windVel = K * Vector3(-(aux.z - origin.z) + 2.0, aux.x - origin.x, 0);

	WindGenerator::updateForce(p, t);
}
