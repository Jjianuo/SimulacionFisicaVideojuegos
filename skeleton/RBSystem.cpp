#include "RBSystem.h"

RBSystem::RBSystem() : ParticleSystem()
{
	rb = gPhysics->createRigidStatic(PxTransform({ 0,0,0 }));
	PxShape* s = CreateShape(PxBoxGeometry(50, 0.1, 50));
	rb->attachShape(*s);
	RenderItem* ri = new RenderItem(s, rb, { 1,1,1,1 });
	gScene->addActor(*rb);
}

RBSystem::~RBSystem()
{
	wipe();
}

void RBSystem::update(double t)
{
	for (auto g : _rBGenerators) {
		for (auto pg : g->generateParticles()) {
			_particles.push_back(pg);
		}
	}

	ParticleSystem::update(t);
}

void RBSystem::addGenerator(unsigned type)
{
	switch (type)
	{
	case 1: {
		PxMaterial* mMaterial;
		mMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.1f);

		Particle* auxParticle = new Particle(partType[ICE], true);
		auxParticle->setSize(2);
		auxParticle->setMass(2);
		RigidBodyGenerator* rbGen = new RigidBodyGenerator(auxParticle, mMaterial);
		rbGen->setOrigin({ 20.0f, 50.0f, 0.0f });
		rbGen->setMeanVelocity({ 10,10,10 });
		rbGen->setOffset({ 1,1,1 });

		_rBGenerators.push_back(rbGen);
		delete auxParticle;
		break;
	}
	case 2: {
		PxMaterial* mMaterial;
		mMaterial = gPhysics->createMaterial(0.2f, 0.8f, 0.6f);

		Particle* auxParticle = new Particle(partType[FIRE], true);
		auxParticle->setSize(1);
		auxParticle->setMass(1);
		RigidBodyGenerator* rbGen = new RigidBodyGenerator(auxParticle, mMaterial);
		rbGen->setOrigin({ -20.0f, 50.0f, 0.0f });
		rbGen->setMeanVelocity({ 2,2,2 });
		rbGen->setOffset({ 2,2,2 });

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

	_rigidBodies.push_back(new RigidBody(Vector3(0, 5, 0), 1, CreateShape(PxSphereGeometry(1)), colorsInfo[RED], mMaterial));
}

void RBSystem::wipe()
{
	ParticleSystem::wipe();

	for (auto e : _rigidBodies)
		delete e;
	
}
