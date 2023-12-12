#pragma once
#include "ParticleSystem.h"
#include "RigidBody.h"
#include "RigidBodyGenerator.h"

extern PxPhysics* gPhysics;
extern PxScene* gScene;

class RBSystem : public ParticleSystem
{
	list<Particle*> _rigidBodies;
	list<RigidBodyGenerator*> _rBGenerators;
	PxRigidStatic* rb = nullptr;
public:
	RBSystem();
	~RBSystem();

	void update(double t);

	void addGenerator(unsigned type);
	void generateRB();

	virtual void wipe();
};

