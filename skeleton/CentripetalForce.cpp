#include "CentripetalForce.h"

void CentripetalForce::updateForce(Particle* p, double t)
{
	if (fabs(p->getInvMass()) < 1e-10 || !active) return;
	if (area > 0 && (p->getPose().p.x < origin.x - area || p->getPose().p.x > origin.x + area ||
		p->getPose().p.y < origin.y - area || p->getPose().p.y > origin.y + area ||
		p->getPose().p.z < origin.z - area || p->getPose().p.z > origin.z + area)) return; //out of bounds

	Vector3 f = p->getMass() * (vel * vel) / r * K;
	f.z = 0.0;

	p->addForce(f);
}
