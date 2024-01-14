#include "SquishedTornadoGenerator.h"

void SquishedTornadoGenerator::updateForce(Particle* p, double t)
{
	if (fabs(p->getInvMass()) < 1e-10 || !active) return;
	if (area > 0 && (p->getPose().p.x < origin.x - area || p->getPose().p.x > origin.x + area ||
		p->getPose().p.y < origin.y - area || p->getPose().p.y > origin.y + area ||
		p->getPose().p.z < origin.z - area || p->getPose().p.z > origin.z + area)) return; //out of bounds

	//double x = p->getVelocity().x;
	//double y = p->getVelocity().y;

	double x = linearVel.x;
	double y = linearVel.y;
	double aux = K * K * pow(atan(y / x) -  p->getPose().p.x, 2);
	//double aux = K * K * pow(atan(y / x) - 50, 2);

	Vector3 appVel = Vector3(sqrt(aux - (y * y)), sqrt(aux - (x * x)), 0.0);

	p->addForce(appVel);
}
