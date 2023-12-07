#pragma once
#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"

using namespace physx;

class RigidBody
{
public:
	RigidBody(PxVec3 pos, double m, PxShape* s, PxVec4 c, PxMaterial* mat);
	~RigidBody();

	PxRigidDynamic* rB;
};

