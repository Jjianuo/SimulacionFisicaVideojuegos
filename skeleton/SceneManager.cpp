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
	sceneDesc->gravity = PxVec3(0.0f, -99.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc->cpuDispatcher = gDispatcher;
	sceneDesc->filterShader = contactReportFilterShader;
	sceneDesc->simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(*sceneDesc);

	changeScene(3);
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
	case 3:
	{
		delete rbSys;
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
		break;
	}
	case 1: {
		pSys->update(t);
		break;
	}
	case 2: {
		rbSys->update(t);
		break;
	}
	case 3: {
		gameSys->update(t);
		break;
	}
	default:
		break;
	}
}

void SceneManager::handleMotion(double x, double y)
{
	if(gameSys != nullptr)
		gameSys->handleMotion(x);
}

void SceneManager::mouseClick(int button, int state, int x, int y)
{
	if (gameSys != nullptr)
		gameSys->mouseClick(button, state, x, y);
}

void SceneManager::keyPress(unsigned char key, const PxTransform& camera)
{
	switch (toupper(key)) {
		case '0': {
			changeScene(0);
			break;
		}
		case '1': {
			changeScene(1);
			break;
		}
		case '2': {
			changeScene(2);
			break;
		}
		case '3': {
			changeScene(3);
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
			break;
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
			break;
		}
		case 2:
		{
			switch (toupper(key))
			{
			case 'Z': {
				rbSys->generateRB();
				break;
			}
			case 'X': {
				//rbSys->addGenerator(1);
				//rbSys->addGenerator(2);
				rbSys->addGenerator(3);
				break;
			}
			case 'C': {
				rbSys->addGenerator(4);
				//rbSys->addGenerator(2);
				//rbSys->addGenerator(3);
				break;
			}
			default:
				break;
			}
			break;
		}
		case 3: //juego
		{
			switch (toupper(key)) {
			case 'S': {
				gameSys->shake(true);
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

void SceneManager::onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	if(gameSys != nullptr)
		gameSys->onCollision(actor1, actor2);
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
		rbSys = new RBSystem();
		break;
	}
	case 3: //juego
	{
		gameSys = new GameSystem();
		gameSys->gameSetup();
		GetCamera()->setEye(PxVec3({ -50,87,65 }));
		GetCamera()->setDir(PxVec3({ 0,0,-45 }));
		break;
	}
	default:
		break;
	}
}

void SceneManager::clear()
{
	if (gameSys != nullptr)
		gameSys->wipe();
	else if(rbSys != nullptr)
		rbSys->wipe();
	else if(pSys != nullptr)
		pSys->wipe();

	gameSys = nullptr;
	rbSys = nullptr;
	pSys = nullptr;

	gScene->release();
	gScene = gPhysics->createScene(*sceneDesc);
}

int SceneManager::getScore()
{
	if (gameSys == nullptr)
		return -1;
	return gameSys->getScore();
}

int SceneManager::getGameState()
{
	if (gameSys == nullptr)
		return -1;
	return gameSys->getGameState();
}
