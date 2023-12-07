#include "SceneManager.h"

SceneManager::SceneManager() 
{
	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport, PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(), true, gPvd);

	// coef rozamiento estático, coef rozamiento dinámico, coeficiente elástico
	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	sceneDesc = new PxSceneDesc(gPhysics->getTolerancesScale());
	sceneDesc->gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc->cpuDispatcher = gDispatcher;
	sceneDesc->filterShader = contactReportFilterShader;
	sceneDesc->simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(*sceneDesc);

	changeScene(2);
}

SceneManager::~SceneManager()
{
	clear();
	switch (currScene)
	{
	case 0:
	{
		delete shoot;
		delete pSys;
		break;
	}
	case 1:
	{
		delete pSys;
		break;
	}
	case 2:
	{
		delete pSys;
		break;
	}
	default:
		break;
	}

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();

	gFoundation->release();

	for (auto e : particles)
		delete e;
}

void SceneManager::update(double t)
{
	gScene->simulate(t);
	gScene->fetchResults(true);

	switch (currScene)
	{
	case 0: {
		shoot->integrate(t);
		pSys->update(t);
	}
	case 1: {
		pSys->update(t);
	}
	default:
		break;
	}

	for (auto e : particles)
		e->integrate(t);
}

void SceneManager::keyPress(unsigned char key, const PxTransform& camera)
{
	switch (toupper(key)) {
		case '0': {
			currScene = 0;
			changeScene(0);
			break;
		}
		case '1': {
			currScene = 1;
			changeScene(1);
			break;
		}
		default:
			break;
	}
	switch (currScene)
	{
		case 0:
		{
			switch (toupper(key))
			{
			case 'P':
			{
				shoot->shoot(Shooter::PISTOL);
				break;
			}
			case 'L':
			{
				shoot->shoot(Shooter::LASER);
				break;
			}
			case 'K':
			{
				shoot->shoot(Shooter::ARTILLERY);
				break;
			}
			case 'B':
			{
				shoot->shoot(Shooter::FIREBALL);
				break;
			}
			case 'M':
			{
				pSys->addGenerator(9);
				break;
			}
			case 'F' :
			{
				pSys->generateFirework(0);
				break;
			}
			case 'G':
			{
				pSys->generateFirework(1);
				break;
			}
			case 'H':
			{
				pSys->generateFirework(2);
				break;
			}
			case 'J':
			{	pSys->generateFirework(3);
				break;
			}
			default:
				break;
			}
		}
		case 1: 
		{
			switch (toupper(key))
			{
			case 'Z': {
				pSys->generateSlinkyDemo();
				break;
			}
			case 'X': {
				pSys->generateSpringDemo2();
				break;
			}
			case 'C': {
				pSys->generateSpringDemo();
				break;
			}
			case 'V':
			{
				pSys->addGenerator(3);
				pSys->addGenerator(4);
				pSys->addGenerator(5);
				break;
			}
			case 'B':
			{
				pSys->generateForce(1);
				break;
			}
			case 'N':
			{
				pSys->generateBuoyancyDemo();
				break;
			}
			default:
				break;
			}
		}
		case 2:
		{
			switch (toupper(key))
			{
			case 'Z': {
				pSys->generateRB();
				break;
			}
			default:
				break;
			}
			break;
		}
		default:
			break;
	}
}

void SceneManager::changeScene(int scene)
{
	clear();
	currScene = scene;
	switch (currScene)
	{
	case 0:
	{
		shoot = new Shooter();
		pSys = new ParticleSystem();
		break;
	}
	case 1: 
	{
		pSys = new ParticleSystem();
		break;
	}
	case 2:
	{
		PxRigidStatic* rb = gPhysics->createRigidStatic(PxTransform({ 0,0,0 }));
		PxShape* s = CreateShape(PxBoxGeometry(50, 0.1, 50));
		rb->attachShape(*s);
		RenderItem* ri = new RenderItem(s, rb, { 1,1,1,1 });
		gScene->addActor(*rb);
		pSys = new ParticleSystem();
		break;
	}
	default:
		break;
	}
}

void SceneManager::clear()
{
	if(pSys != nullptr)
		pSys->wipe();
	gScene->release();
	gScene = gPhysics->createScene(*sceneDesc);
}
