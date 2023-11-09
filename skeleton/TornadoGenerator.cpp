#include "TornadoGenerator.h"

void TornadoGenerator::updateForce(Particle* p, double t)
{
	const Vector3 aux = p->getPose().p;
	windVel = K * Vector3(-(aux.z - origin.z), 50 - (aux.y - origin.y), aux.x - origin.x);

	WindGenerator::updateForce(p, t);
}
