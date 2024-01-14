#pragma once
#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"
#include "Particle.h"

using namespace physx;

class RigidBody : public Particle
{
protected:
	PxMaterial* material = nullptr;
	RenderItem* ri = nullptr;
	PxSphereGeometry geometry;
public:
	RigidBody(Vector3 pos, double m, PxShape* s, PxVec4 c, PxMaterial* mat, Vector3 inertiaTensor = {-1,-1,-1});
	RigidBody(Vector3 pos, double m, PxShape* s, PxVec4 c, Vector3 mat, Vector3 inertiaTensor = { -1,-1,-1 });
	RigidBody(Particle* p, Vector3 pos, double m, PxShape* s, PxVec4 c, Vector3 mat, Vector3 inertiaTensor = { -1,-1,-1 });
	~RigidBody();

	PxRigidDynamic* rB;

	RigidBody* clone() const;
	inline virtual void die() { 
		if (ri != nullptr) 
			ri->release(); 
		ri = nullptr; 
		if (rB != nullptr) 
			rB->release(); 
		rB = nullptr; 
		pInfo.alive = false; 
	};
	virtual void addForce(const Vector3& f);
	virtual void clearForce();
	virtual PxTransform getPose();
	virtual Vector3 getVelocity();
	virtual void setVelocity(const Vector3& v);
	PxGeometry getGeometry();

	virtual void setInertiaTensor(const Vector3& inertiaTensor);
	void release();
};

