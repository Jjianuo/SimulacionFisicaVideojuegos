#include "GameSystem.h"

GameSystem::GameSystem() : RBSystem()
{
	_mt = std::mt19937{ std::random_device()() };

	randomFruit();
}

void GameSystem::update(double t)
{
	RBSystem::update(t);

	currFruit->setPos({ (((float)pointerPos - 250 - (float)(GLdouble(glutGet(GLUT_WINDOW_WIDTH)) / 2)) / 5), 140, -45});

	while (!genQueue.empty()) {
		combineFruit(genQueue.front().first, genQueue.front().second); genQueue.pop();
	}
}

void GameSystem::handleMotion(double x)
{
	pointerPos = x;
}

void GameSystem::mouseClick(int button, int state, int x, int y)
{
	//std::cout << button << " " << state << "\n";
	if (button == 0 && state == 0) {

		Fruit* fruit = new Fruit(currFruit, currFruit->getPose().p, currFruit->getMass(),
			CreateShape(PxSphereGeometry(currFruit->getSize())), currFruit->getColor(), Vector3(0.5f, 0.5f, 0.0f));
		_particles.push_back(fruit);
		rels.insert({ fruit->getActor(), fruit });


		currFruit->die();
		randomFruit();
	}
}

void GameSystem::onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	auto fruit1 = rels.find(actor1);
	if (fruit1 != rels.end()) {
		auto fruit2 = rels.find(actor2);
		if (fruit2 != rels.end()) {
			if (fruit1->second->getType() == fruit2->second->getType()) {
				genQueue.push({ fruit1->second, fruit2->second });

				rels.erase(fruit1);
				rels.erase(fruit2);
			}
		}
	}

}

void GameSystem::gameSetup()
{
	PxRigidStatic* leftWall = gPhysics->createRigidStatic(PxTransform({ -88.5,80,-50 }));
	PxShape* s = CreateShape(PxBoxGeometry(1.5, 50, 10));
	leftWall->attachShape(*s);
	RenderItem* ri = new RenderItem(s, leftWall, { 0.39,0.24,0.16,1 });
	gScene->addActor(*leftWall);

	PxRigidStatic* rightWall = gPhysics->createRigidStatic(PxTransform({ -11.5,80,-50 }));
	s = CreateShape(PxBoxGeometry(1.5, 50, 10));
	rightWall->attachShape(*s);
	RenderItem* ri2 = new RenderItem(s, rightWall, { 0.39,0.24,0.16,1 });
	gScene->addActor(*rightWall);

	PxRigidStatic* backWall = gPhysics->createRigidStatic(PxTransform({ -50,80,-65 }));
	s = CreateShape(PxBoxGeometry(40, 50, 1.5));
	backWall->attachShape(*s);
	RenderItem* ri3 = new RenderItem(s, backWall, { 0.39,0.24,0.16,1 });
	gScene->addActor(*backWall);
}

void GameSystem::randomFruit()
{
	int f = _uFruit(_mt) + 10;

	currFruit = new Particle(partType[f], true);
	currFruit->setSize(currFruit->getSize() * 6);
}

void GameSystem::combineFruit(Fruit* fruit1, Fruit* fruit2)
{

	Vector3 newPos = (fruit1->getPos() + fruit2->getPos() + Vector3(0.0, 5.0, 0.0)) / 2;

	cout << newPos.x << " " << newPos.y << " " << newPos.z << "\n";
	fruit1->die();
	fruit2->die();

	Particle* nextFruit = new Particle(partType[fruit1->getType() + 1], true);
	nextFruit->setSize(nextFruit->getSize() * 6);

	Fruit* genfruit = new Fruit(nextFruit, newPos, nextFruit->getMass(),
		CreateShape(PxSphereGeometry(nextFruit->getSize())), nextFruit->getColor(), Vector3(0.5f, 0.5f, 0.0f));

	_particles.push_back(genfruit);
	rels.insert({ genfruit->getActor(), genfruit });

	nextFruit->die();

}
