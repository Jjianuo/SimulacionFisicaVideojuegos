#pragma once
#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"
#include "Particle.h"

using namespace physx;

class RigidBody : public Particle
{
	PxMaterial* material = nullptr;
	RenderItem* ri = nullptr;
public:
	RigidBody(Vector3 pos, double m, PxShape* s, PxVec4 c, PxMaterial* mat);
	RigidBody(Vector3 pos, double m, PxShape* s, PxVec4 c, Vector3 mat);
	~RigidBody();

	void setVelocity(Vector3 v);

	PxRigidDynamic* rB;

	RigidBody* clone() const;
	inline virtual void die() { if (ri != nullptr) ri->release(); Particle::die(); };
	virtual void addForce(const Vector3& f);
	virtual void setPos(const Vector3& f);
};

