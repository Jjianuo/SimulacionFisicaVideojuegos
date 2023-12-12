#include "RigidBody.h"

extern PxPhysics* gPhysics;
extern PxScene* gScene;

RigidBody::RigidBody(PxVec3 pos, double m, PxShape* s, PxVec4 c, PxMaterial* mat)  : Particle(false)
{
	rB = gPhysics->createRigidDynamic(PxTransform(pos));
	rB->setMass(m);
	s->setMaterials(&mat, 1);
	material = mat;
	rB->attachShape(*s);
	ri = new RenderItem(s, rB, c);
	gScene->addActor(*rB);

	//PxRigidBodyExt::updateMassAndInertia(rB, m * s.);
}

RigidBody::RigidBody(Vector3 pos, double m, PxShape* s, PxVec4 c, Vector3 mat)
{
	PxMaterial* mMaterial;
	mMaterial = gPhysics->createMaterial(mat.x, mat.y, mat.z);

	rB = gPhysics->createRigidDynamic(PxTransform(pos));
	rB->setMass(m);
	s->setMaterials(&mMaterial, 1);
	material = mMaterial;
	rB->attachShape(*s);
	ri = new RenderItem(s, rB, c);
	gScene->addActor(*rB);
}

RigidBody::~RigidBody()
{
	if (ri != nullptr)
		ri->release();
}

void RigidBody::setVelocity(Vector3 v)
{
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
	rB->addForce(f);
}

void RigidBody::setPos(const Vector3& f)
{

}
