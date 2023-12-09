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
	RenderItem* ri = new RenderItem(s, rB, c);
	gScene->addActor(*rB);

	//PxRigidBodyExt::updateMassAndInertia(rB, m * s.);
}

//RigidBody::RigidBody(Particle* p, PxMaterial* mat)
//{
//}

RigidBody::~RigidBody()
{
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
