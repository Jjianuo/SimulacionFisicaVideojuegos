#include "RigidBody.h"
#include <iostream>


extern PxPhysics* gPhysics;
extern PxScene* gScene;

RigidBody::RigidBody(PxVec3 pos, double m, PxShape* s, PxVec4 c, PxMaterial* mat, Vector3 inertiaTensor)  : Particle(false)
{
	rB = gPhysics->createRigidDynamic(PxTransform(pos));
	rB->setMass(m);
	s->setMaterials(&mat, 1);
	material = mat;
	rB->attachShape(*s);
	ri = new RenderItem(s, rB, c);
	gScene->addActor(*rB);
	ri->shape->getSphereGeometry(geometry);

	if (inertiaTensor == Vector3(-1, -1, -1))
		PxRigidBodyExt::setMassAndUpdateInertia(*rB, m);
	else
		rB->setMassSpaceInertiaTensor({ inertiaTensor.y * inertiaTensor.z,
			inertiaTensor.x * inertiaTensor.z, inertiaTensor.x * inertiaTensor.y });
		//rB->setMassSpaceInertiaTensor(inertiaTensor);
}

RigidBody::RigidBody(Vector3 pos, double m, PxShape* s, PxVec4 c, Vector3 mat, Vector3 inertiaTensor) : Particle(false)
{
	PxMaterial* mMaterial;
	mMaterial = gPhysics->createMaterial(mat.x, mat.y, mat.z);

	rB = gPhysics->createRigidDynamic(PxTransform(pos));
	s->setMaterials(&mMaterial, 1);
	material = mMaterial;
	rB->attachShape(*s);
	ri = new RenderItem(s, rB, c);
	gScene->addActor(*rB);
	ri->shape->getSphereGeometry(geometry);

	if (inertiaTensor == Vector3(-1, -1, -1))
		PxRigidBodyExt::setMassAndUpdateInertia(*rB, m);
	else
		rB->setMassSpaceInertiaTensor({ inertiaTensor.y * inertiaTensor.z,
			inertiaTensor.x * inertiaTensor.z, inertiaTensor.x * inertiaTensor.y });
}

RigidBody::RigidBody(Particle* p, Vector3 pos, double m, PxShape* s, PxVec4 c, Vector3 mat, Vector3 inertiaTensor) 
	: Particle(p, false)
{
	PxMaterial* mMaterial;
	mMaterial = gPhysics->createMaterial(mat.x, mat.y, mat.z);

	rB = gPhysics->createRigidDynamic(PxTransform(pos));
	s->setMaterials(&mMaterial, 1);
	material = mMaterial;
	rB->attachShape(*s);
	ri = new RenderItem(s, rB, c);
	gScene->addActor(*rB);
	ri->shape->getSphereGeometry(geometry);

	if (inertiaTensor == Vector3(-1, -1, -1))
		PxRigidBodyExt::setMassAndUpdateInertia(*rB, m);
	else
		rB->setMassSpaceInertiaTensor({ inertiaTensor.y * inertiaTensor.z,
			inertiaTensor.x * inertiaTensor.z, inertiaTensor.x * inertiaTensor.y });
}

RigidBody::~RigidBody()
{
	die();
}

void RigidBody::setVelocity(Vector3 v)
{
	if (rB != nullptr)
		rB->setLinearVelocity(v);
}

RigidBody* RigidBody::clone() const
{
	PxShape* s = CreateShape(PxSphereGeometry(this->pInfo.size));
	RigidBody* aux = new RigidBody(this->pInfo.pose.p, this->pInfo.mass, s, this->pInfo.color, material);
	aux->getPInfo() = this->pInfo;
	aux->setVelocity(rB->getLinearVelocity());
	return aux;
}

void RigidBody::addForce(const Vector3& f)
{
	if(rB != nullptr)
		rB->addForce(f);
}

PxTransform RigidBody::getPose()
{
	if (rB == nullptr) 
		return { -999, -999, -999 };
	return rB->getGlobalPose();
}

PxGeometry RigidBody::getGeometry()
{
	return geometry;
}

void RigidBody::setInertiaTensor(const Vector3& inertiaTensor)
{
	rB->setMassSpaceInertiaTensor({ inertiaTensor.y * inertiaTensor.z,
	inertiaTensor.x * inertiaTensor.z, inertiaTensor.x * inertiaTensor.y });
}

void RigidBody::release()
{
}
