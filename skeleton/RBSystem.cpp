#include "RBSystem.h"

RBSystem::RBSystem() : ParticleSystem()
{
	PxMaterial* mMaterial;
	mMaterial = gPhysics->createMaterial(0.5, 0.5, 0.0);

	rb = gPhysics->createRigidStatic(PxTransform({ -50,30,-50 }));
	PxShape* s = CreateShape(PxBoxGeometry(40, 1.5, 10), mMaterial);
	rb->attachShape(*s);
	RenderItem* ri = new RenderItem(s, rb, { 0.39,0.24,0.16,1 });
	gScene->addActor(*rb);

	//PxMaterial* mMaterial;
	//mMaterial = gPhysics->createMaterial(0.5, 0.5, 0.5);

	//rb = gPhysics->createRigidStatic(PxTransform({ 0,0,0 }));
	//PxShape* s = CreateShape(PxBoxGeometry(90, 0.1, 90), mMaterial);
	//rb->attachShape(*s);
	//RenderItem* ri = new RenderItem(s, rb, { 0.39,0.24,0.16,1 });
	//gScene->addActor(*rb);
}

RBSystem::~RBSystem()
{
	wipe();
}

void RBSystem::update(double t)
{
	//for (auto g : _rBGenerators) {
	//	for (auto pg : g->generateParticles()) {
	//		_particles.push_back(pg);
	//	}
	//}

	ParticleSystem::update(t);
}

void RBSystem::addGenerator(unsigned type)
{
	switch (type)
	{
	case 1: {
		PxMaterial* mMaterial;
		mMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.1f);

		Particle* auxParticle = new Particle(partType[ICE], false);
		auxParticle->setSize(2);
		auxParticle->setMass(2);
		dem = new RigidBodyGenerator(auxParticle, mMaterial);
		dem->setOrigin({ 20.0f, 50.0f, 0.0f });
		dem->setMeanVelocity({ 1,1,1 });
		dem->setOffset({ 1,1,1 });

		auxParticle->die();
		_pGenerator.push_back(dem);
		break;
	}
	case 2: {
		PxMaterial* mMaterial;
		mMaterial = gPhysics->createMaterial(0.2f, 0.8f, 0.6f);

		Particle* auxParticle = new Particle(partType[FIRE], false);
		auxParticle->setShape(PxGeometryType::eBOX);
		auxParticle->setSize(1);
		auxParticle->setMass(10);
		RigidBodyGenerator* rbGen = new RigidBodyGenerator(auxParticle, mMaterial, {0.0,0.0,0.0}, {0.0,0.0,0.0}, { 10.0, 0.0, 0.0 });
		rbGen->setOrigin({ -20.0f, 50.0f, 0.0f });
		rbGen->setMeanVelocity({ 2,2,2 });
		rbGen->setOffset({ 2,2,2 });

		_pGenerator.push_back(rbGen);

		auxParticle->die();
		break;
	}	
	case 3: {
		PxMaterial* mMaterial;
		mMaterial = gPhysics->createMaterial(0.8f, 0.5f, 0.1f);

		Particle* auxParticle = new Particle(partType[CHERRY_BLOSSOM], false);
		auxParticle->setMass(10);
		auxParticle->setShape(PxGeometryType::eBOX);
		RigidBodyGenerator* rbGen = new RigidBodyGenerator(auxParticle, mMaterial, { 0.0,0.0,0.0 }, { 0.0,0.0,0.0 });
		rbGen->setOrigin({ 0.0f, 50.0f, 20.0f });
		rbGen->setMeanVelocity({ 1,1,1 });
		rbGen->setOffset({ 5,5,5 });

		WindGenerator* windGen = new WindGenerator();
		windGen->setArea(70.0);
		windGen->setOrigin({ 0.0f, 20.0f, 20.0f });
		pfr.addPaticleGenerator(windGen, rbGen);

		_pGenerator.push_back(rbGen);

		auxParticle->die();
		break;
	}
	case 4: {
		ExplosiveForce* aux = new ExplosiveForce();
		aux->setOrigin({ 20.0f, 40.0f, 0.0f });
		pfr.addPaticleGenerator(aux, dem);
		cout << "BOOOM\n";
		break;
	}
	default:
		break;
	}
}

void RBSystem::generateForce(unsigned type)
{
}

void RBSystem::generateRB()
{
	PxMaterial* mMaterial;
	mMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.1f);

	_particles.push_back(new RigidBody(Vector3(0, 5, 0), 1, CreateShape(PxSphereGeometry(1)), colorsInfo[RED], mMaterial));
}

void RBSystem::wipe()
{
	ParticleSystem::wipe();
}
