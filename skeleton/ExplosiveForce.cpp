#include "ExplosiveForce.h"

void ExplosiveForce::updateForce(Particle* p, double t)
{
    if (fabs(p->getInvMass()) < 1e-10) return;

    double aux = _t * (area / dur);
    Vector3 pos = p->getPose().p;
    //double r = sqrt(pow(pos.x - origin.x, 2) + pow(pos.y - origin.y, 2) + pow(pos.z - origin.z, 2));
    double r = (pos - origin).magnitude();
    if (r >= aux) return;
    if (r < 1e-10) r = 0.1;

    Vector3 expF = (K/ pow(r, 2)) * (pos - origin) * exp(-(t / dur));
    p->addForce(expF);
}
