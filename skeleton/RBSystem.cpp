#include "RBSystem.h"

RBSystem::RBSystem() : ParticleSystem()
{
	PxRigidStatic* rb = gPhysics->createRigidStatic(PxTransform({ 0,0,0 }));
	PxShape* s = CreateShape(PxBoxGeometry(50, 0.1, 50));
	rb->attachShape(*s);
	RenderItem* ri = new RenderItem(s, rb, { 1,1,1,1 });
	gScene->addActor(*rb);
}

RBSystem::~RBSystem()
{
	for (auto e : _rigidBodies)
		delete e;
}

void RBSystem::update(double t)
{
	ParticleSystem::update(t);

	for (auto g : _rBGenerators) {
		for (auto pg : g->generateParticles()) {
			_rigidBodies.push_back(pg);
		}
	}
}

void RBSystem::addGenerator(unsigned type)
{
	switch (type)
	{
	case 1: {
		PxMaterial* mMaterial;
		mMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.1f);

		Particle* auxParticle = new Particle(partType[ICE], true);
		auxParticle->getSize() = 0.2;
		auxParticle->getMass() = 10;
		RigidBodyGenerator* rbGen = new RigidBodyGenerator(auxParticle, mMaterial);
		rbGen->setMeanVelocity({ 1, 6, 1 });
		rbGen->setOrigin({ 0.0f, 50.0f, 0.0f });
		rbGen->setOffset({ 20,20,20 });

		_rBGenerators.push_back(rbGen);
		delete auxParticle;
		break;
	}
	default:
		break;
	}
}

void RBSystem::generateRB()
{
	PxMaterial* mMaterial;
	mMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.1f);

	_rigidBodies.push_back(new RigidBody(PxVec3(0, 5, 0), 1, CreateShape(PxSphereGeometry(1)), colorsInfo[RED], mMaterial));
}
