#include "Fruit.h"

Fruit::Fruit(Vector3 pos, double m, PxShape* s, PxVec4 c, PxMaterial* mat, Vector3 inertiaTensor) 
	: RigidBody(pos, m, s, c, mat, inertiaTensor)
{
	rB->setRigidDynamicLockFlag(PxRigidDynamicLockFlag::eLOCK_LINEAR_Z, true);
	//rB->setRigidDynamicLockFlag(PxRigidDynamicLockFlag::eLOCK_ANGULAR_Z, true);

}

Fruit::Fruit(Vector3 pos, double m, PxShape* s, PxVec4 c, Vector3 mat, Vector3 inertiaTensor)
	: RigidBody(pos, m, s, c, mat, inertiaTensor)
{
	rB->setRigidDynamicLockFlag(PxRigidDynamicLockFlag::eLOCK_LINEAR_Z, true);
	//rB->setRigidDynamicLockFlag(PxRigidDynamicLockFlag::eLOCK_ANGULAR_Z, true);

}

Fruit::Fruit(Particle* p, Vector3 pos, double m, PxShape* s, PxVec4 c, Vector3 mat, Vector3 inertiaTensor)
	: RigidBody(p, pos, m, s, c, mat, inertiaTensor)
{
	rB->setRigidDynamicLockFlag(PxRigidDynamicLockFlag::eLOCK_LINEAR_Z, true);
	//rB->setRigidDynamicLockFlag(PxRigidDynamicLockFlag::eLOCK_ANGULAR_Z, true);

}

PxActor* Fruit::getActor()
{
	return rB;
}

void Fruit::setPos(PxVec3 p)
{
	rB->setGlobalPose(PxTransform(p));
}
