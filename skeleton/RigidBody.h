#pragma once
#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"
#include "Particle.h"

using namespace physx;

class RigidBody : public Particle
{
	PxMaterial* material = nullptr;
public:
	RigidBody(PxVec3 pos, double m, PxShape* s, PxVec4 c, PxMaterial* mat);
	//RigidBody(Particle* p, PxMaterial* mat = nullptr);
	~RigidBody();

	void setVelocity(Vector3 v);

	PxRigidDynamic* rB;

	RigidBody* clone() const;
};

