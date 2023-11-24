#include "SpringForce.h"

void SpringForce::updateForce(Particle* p, double t)
{
	Vector3 rel_pos = other->getPose().p - p->getPose().p;

	const float length = rel_pos.normalize();
	const float delta_x = length - restingLength;

	Vector3 force = rel_pos * delta_x * K;

	p->addForce(force);
}