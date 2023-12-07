#include "RigidBody.h"

extern PxPhysics* gPhysics;
extern PxScene* gScene;

RigidBody::RigidBody(PxVec3 pos, double m, PxShape* s, PxVec4 c, PxMaterial* mat) 
{
	rB = gPhysics->createRigidDynamic(PxTransform(pos));
	rB->setMass(m);
	s->setMaterials(&mat, 1);
	rB->attachShape(*s);
	RenderItem* ri = new RenderItem(s, rB, c);
	gScene->addActor(*rB);

	//PxRigidBodyExt::updateMassAndInertia(rB, m * s.);
}

RigidBody::~RigidBody()
{
}
