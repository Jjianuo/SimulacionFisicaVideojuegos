#include "ExplosiveForce.h"

void ExplosiveForce::updateForce(Particle* p, double t)
{
    if (fabs(p->getInvMass()) < 1e-10 || !active) return;

    double aux = (area / dur) * _t;
    Vector3 pos = p->getPose().p;
    //double r = sqrt(pow(pos.x - origin.x, 2) + pow(pos.y - origin.y, 2) + pow(pos.z - origin.z, 2));
    double r = (pos - origin).magnitude();
    if (r >= aux) return;
    if (r < 1e-10) r = 0.1;

    Particle* aaa = new Particle(true);
    aaa->setPos(pos);
    aaa->setColor({ 1.0,1.0,1.0, 0.1 });

    Vector3 expF = (K/ pow(r, 2)) * (pos - origin) * exp(-(_t / dur));
    p->addForce(expF);
}
