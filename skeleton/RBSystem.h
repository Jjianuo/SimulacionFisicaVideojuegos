#pragma once
#include "ParticleSystem.h"
#include "RigidBody.h"
#include "RigidBodyGenerator.h"

extern PxPhysics* gPhysics;
extern PxScene* gScene;

class RBSystem : public ParticleSystem
{
	PxRigidStatic* rb = nullptr;
	RigidBodyGenerator* dem;
public:
	RBSystem();
	~RBSystem();

	virtual void update(double t);

	virtual void addGenerator(unsigned type);
	virtual void generateForce(unsigned type);

	void generateRB();

	virtual void wipe();
};

