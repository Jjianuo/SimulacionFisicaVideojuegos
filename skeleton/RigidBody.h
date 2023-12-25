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
	RigidBody(Vector3 pos, double m, PxShape* s, PxVec4 c, PxMaterial* mat, Vector3 inertiaTensor = {-1,-1,-1});
	RigidBody(Vector3 pos, double m, PxShape* s, PxVec4 c, Vector3 mat, Vector3 inertiaTensor = { -1,-1,-1 });
	RigidBody(Particle* p, Vector3 pos, double m, PxShape* s, PxVec4 c, Vector3 mat, Vector3 inertiaTensor = { -1,-1,-1 });
	~RigidBody();

	void setVelocity(Vector3 v);

	PxRigidDynamic* rB;

	RigidBody* clone() const;
	inline virtual void die() { if (ri != nullptr) ri->release(); ri = nullptr; if (rB != nullptr) rB->release(); rB = nullptr; };
	virtual void addForce(const Vector3& f);
	virtual Vector3 getPos();
	virtual void setInertiaTensor(const Vector3& inertiaTensor);
	void release();
};

