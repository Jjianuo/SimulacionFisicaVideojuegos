#include "ExplosiveForce.h"

void ExplosiveForce::updateForce(Particle* p, double t)
{
    if (fabs(p->getInvMass()) < 1e-10) return;

    Vector3 pos = p->getPose().p;
    //double r = sqrt(pow(pos.x - origin.x, 2) + pow(pos.y - origin.y, 2) + pow(pos.z - origin.z, 2));
    double r = pos.magnitude();

    double aux2 = pow(e, -(t / dur));
    Vector3 expF = (K/ pow(r, 2)) * (pos - origin) * aux2;
    p->addForce(expF);
}
