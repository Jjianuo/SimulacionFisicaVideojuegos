#include "RigidBodyGenerator.h"

void RigidBodyGenerator::setVars()
{
	_n = std::normal_distribution<float>(minVar, maxVar);
}

Vector3 RigidBodyGenerator::getRandomDist()
{
	return Vector3(_n(_mt), _n(_mt), _n(_mt));
}

RigidBodyGenerator::RigidBodyGenerator(PxMaterial* mat, Vector3 origin, Vector3 mean_velocity)
{
	_origin = origin;
	_mean_velocity = mean_velocity;
	Particle* p = new Particle(false);

	RigidBody* rb = new RigidBody(_origin, p->getMass(), CreateShape(PxSphereGeometry(p->getSize())), p->getColor(), mat);
	rb->getPInfo() = p->getPInfo();
	rb->setVelocity(_mean_velocity);
	setParticle(rb);
	_mt = std::mt19937{ std::random_device()() };
}

RigidBodyGenerator::RigidBodyGenerator(Particle* p, PxMaterial* mat, Vector3 origin, Vector3 mean_velocity)
{
	//Vector3 pos, Vector3 Vel, Vector3 Acc, double m, double damp, double ls, PxShape* s, Vector4 c
	_origin = origin;
	_mean_velocity = mean_velocity;

	RigidBody* rb = new RigidBody(_origin, p->getMass(), CreateShape(PxSphereGeometry(p->getSize())), p->getColor(), mat);
	rb->getPInfo() = p->getPInfo();
	rb->setVelocity(_mean_velocity);
	setParticle(rb);
	_mt = std::mt19937{ std::random_device()() };
}
