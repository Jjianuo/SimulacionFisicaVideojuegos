#include "WindGenerator.h"

void WindGenerator::updateForce(Particle* p, double t)
{
    if (fabs(p->getInvMass()) < 1e-10) return;
    if (area > 0 && (p->getPose().p.x < origin.x - area || p->getPose().p.x > origin.x + area ||
        p->getPose().p.y < origin.y - area || p->getPose().p.y > origin.y + area ||
        p->getPose().p.z < origin.z - area || p->getPose().p.z > origin.z + area)) return; //out of bounds

    double areaEffe = 4 * PI * pow(p->getSize(), 2); //área efectiva del objeto que se enfrenta al viento 
    k2 = areaEffe * dragCoef * airDensity; 


    Vector3 v = windVel - p->getVelocity();
    // Apply the wind force
    Vector3 windF = (k1 + k2 * v.magnitude()) * v;
    p->addForce(windF);
}
