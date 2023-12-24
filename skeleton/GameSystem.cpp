#include "GameSystem.h"

GameSystem::GameSystem() : RBSystem()
{
	_mt = std::mt19937{ std::random_device()() };

	int f = _uFruit(_mt) + 10;
	//std::cout << partType[f].color.x << " " << partType[f].color.y << " " << partType[f].color.z << "\n";

	currFruit = new Particle(partType[f], true);
	currFruit->setSize(currFruit->getSize() * 6);
}

void GameSystem::update(double t)
{
	RBSystem::update(t);

	currFruit->setPos({ (((float)pointerPos - 250 - (float)(GLdouble(glutGet(GLUT_WINDOW_WIDTH)) / 2)) / 5), 140, -50});
}

void GameSystem::handleMotion(double x)
{
	pointerPos = x;
}

void GameSystem::gameSetup()
{
	PxRigidStatic* leftWall = gPhysics->createRigidStatic(PxTransform({ -88.5,80,-50 }));
	PxShape* s = CreateShape(PxBoxGeometry(1.5, 50, 7));
	leftWall->attachShape(*s);
	RenderItem* ri = new RenderItem(s, leftWall, { 0.39,0.24,0.16,1 });
	gScene->addActor(*leftWall);

	PxRigidStatic* rightWall = gPhysics->createRigidStatic(PxTransform({ -11.5,80,-50 }));
	s = CreateShape(PxBoxGeometry(1.5, 50, 7));
	rightWall->attachShape(*s);
	RenderItem* ri2 = new RenderItem(s, rightWall, { 0.39,0.24,0.16,1 });
	gScene->addActor(*rightWall);

	PxRigidStatic* backWall = gPhysics->createRigidStatic(PxTransform({ -50,80,-55 }));
	s = CreateShape(PxBoxGeometry(40, 50, 1.5));
	backWall->attachShape(*s);
	RenderItem* ri3 = new RenderItem(s, backWall, { 0.39,0.24,0.16,1 });
	gScene->addActor(*backWall);
}
