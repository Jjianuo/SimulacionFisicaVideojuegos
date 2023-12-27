#include "GameSystem.h"

GameSystem::GameSystem() : RBSystem(), fruitScale(11.5)
{
	_mt = std::mt19937{ std::random_device()() };

	randomFruit();
	dropIndicator = new Particle(false);
	dropIndicator->setRenderItem(CreateShape(PxBoxGeometry(0.5, 55, 0.5)), { 0,0,0 }, colorsInfo[WHITE]);

	cloud = new UniformParticleGenerator();
	Particle* mistParticle = new Particle(partType[CLOUD]);
	cloud->setParticle(mistParticle);
	//cloud->setOffset({ 5.0f, 5.0f, 5.0f });
	cloud->setMeanVelocity({ 10.0, 10.0, 10.0 });
	_pGenerator.push_back(cloud);
	delete mistParticle;
}

void GameSystem::update(double t)
{
	RBSystem::update(t);

	Vector3 pointer = { (((float)pointerPos - 250 - (float)(GLdouble(glutGet(GLUT_WINDOW_WIDTH)) / 2)) / 5), 140, -45 };
	//if (pointer.x < (float)(GLdouble(glutGet(GLUT_WINDOW_WIDTH)) / 2)) {
		dropIndicator->setPos({ (((float)pointerPos - 250 - (float)(GLdouble(glutGet(GLUT_WINDOW_WIDTH)) / 2)) / 5), 85, -50});
		currFruit->setPos(pointer);
		cloud->setOrigin(pointer);
	//}


	pfr.updateForces(t);

	while (!genQueue.empty()) {
		combineFruit(genQueue.front().first, genQueue.front().second); genQueue.pop();
	}

	for (auto e : _fruits) {
		if (e->getSize() < partType[e->getType()].size * fruitScale) {
			e->setSize(e->getSize() + 2.5 * t);
			if (e->getSize() > partType[e->getType()].size * fruitScale)
				e->setSize(partType[e->getType()].size * fruitScale);
		}
	}
		//e->clearForce();

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
			CreateShape(PxSphereGeometry(currFruit->getSize())), currFruit->getColor(), Vector3(0.0f, 0.0f, 0.0f));
		_fruits.push_back(fruit);
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
	currFruit->setSize(currFruit->getSize() * fruitScale);
}

Fruit* GameSystem::combineFruit(Fruit* fruit1, Fruit* fruit2)
{
	//Vector3 newPos = (fruit1->getPose().p + fruit2->getPose().p) / 2;
	Vector3 newPos = fruit2->getPose().p;

	Particle* nextFruit = new Particle(partType[fruit1->getType() + 1], true);
	nextFruit->setSize(fruit1->getSize());

	Vector3 offset = Vector3(0.0, (nextFruit->getSize() - fruit1->getSize()), 0.0);
	ExplosiveForce* makeSpace = new ExplosiveForce(newPos, 100000, (nextFruit->getSize() + nextFruit->getSize() - fruit1->getSize()) * 2);
	//ExplosiveForce* makeSpace = new ExplosiveForce(newPos, 18000, nextFruit->getSize() * 2.5);

	fruit1->die();
	fruit2->die();

	for (auto it = _fruits.begin(); it != _fruits.end();) {
		if (*it == fruit1 || *it == fruit2)
			it = _fruits.erase(it);
		else {
			pfr.addRegistry(makeSpace, *it);
			++it;
		}
	}

	Fruit* genfruit = new Fruit(nextFruit, newPos, nextFruit->getMass(),
		CreateShape(PxSphereGeometry(nextFruit->getSize())), nextFruit->getColor(), Vector3(0.0f, 0.0f, 0.0f));

	_fruits.push_back(genfruit);
	rels.insert({ genfruit->getActor(), genfruit });

	nextFruit->die();

	return genfruit;
}
