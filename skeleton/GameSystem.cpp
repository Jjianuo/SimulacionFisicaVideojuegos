#include "GameSystem.h"

Firework* GameSystem::createModelFirework()
{
	Firework* temp = new Firework(partType[FIREWORK]);
	temp->changeLifespan(3.4);
	//temp->setAcceleration(temp->getAcceleration() + Vector3{ 0.0, -9.8, 0.0 });

	for (int i = 0; i < 7; ++i) {
		std::shared_ptr<ParticleGenerator> auxGen1(new GaussianParticleGenerator());
		Firework* aux1 = new Firework(partType[DEFAULT]);
		aux1->setColor(colorsInfo[RED + i]);
		aux1->setMass(i);
		auxGen1->setParticle(aux1);
		auxGen1->setNParticles(5);
		temp->addGenerator(auxGen1);
		aux1->die();
	}

	return temp;
}

GameSystem::GameSystem() : RBSystem(), fruitScale(11.5)
{
	_mt = std::mt19937{ std::random_device()() };

	currFruit = randomFruit();
	dropIndicator = new Particle(false);
	dropIndicator->setRenderItem(CreateShape(PxBoxGeometry(0.5, 55, 0.5)), { 0,0,0 }, colorsInfo[WHITE]);

	cloud = new UniformParticleGenerator();
	Particle* mistParticle = new Particle(partType[CLOUD]);
	cloud->setNParticles(5);
	cloud->setParticle(mistParticle);
	delete mistParticle;
	cloud->setMeanVelocity({ 10.0, 10.0, 10.0 });
	_pGenerator.push_back(cloud);

	fireWorks1 = new FireworksGenerator(createModelFirework(), Vector3(-18.5, 0, 0));
	fireWorks1->setActive(false);
	_pGenerator.push_back(fireWorks1);

	fireWorks2 = new FireworksGenerator(createModelFirework(), Vector3(-80.5, 0, 0));
	fireWorks2->setActive(false);
	_pGenerator.push_back(fireWorks2);

	//tornado = new WindGenerator({ -40,0,-45 }, -1, { 0, 5.0, 0 }, 0.07, 0.07);
	tornado = new TornadoGenerator(0.25, { -40,0,-45 }, -1, { 0.1,0.0,0.1 });
	tornado->setActive(false);

	nextFruit = randomFruit();
	nextFruit->setPos(Vector3(0.0, 0.0, 90.0));

	keychain = new Particle(nextFruit);
	keychain->setPos({ 0, 70, -45 });
	keychainAux = new Particle(true);
	keychainAux->setColor(colorsInfo[RED]);
	keychainAux->setPos({ 0, 70, -45 });
	//keychainAux->setSize(3);
	keychainAux->setShape(PxGeometryType::eBOX);
	keychainAux->changeLifespan(-1);

	sf = new SpringForce(20, 5, keychainAux);
	//sf = new ElasticBandForce(100, 5, keychainAux);
	grav = new GravityForceGenerator({ 0.0, -9.8, 0.0 });

	pfr.addRegistry(grav, keychain);
	pfr.addRegistry(sf, keychain);
	_particles.push_back(keychain);
	_particles.push_back(keychainAux);
}

GameSystem::~GameSystem()
{
	currFruit->die();
	keychain->die();
	keychainAux->die();
	nextFruit->die();
	dropIndicator->die();

	leftWall->release();
	rightWall->release();
	backWall->release();
	topWall->release();

	delete currFruit;
	delete keychain;
	delete keychainAux;
	delete nextFruit;
	delete dropIndicator;

	for (auto it = _fruits.begin(); it != _fruits.end();) {
		(*it)->die();
		delete *it;
		it = _fruits.erase(it);
	}
}

void GameSystem::update(double t)
{
	RBSystem::update(t);
	if (shaking) {
		timer += t;
		if (timer >= shakeDuration) {
			shake(false);
			timer = 0;
		}
	}
	else if (win) {
		winTimer += t;
		if (winTimer >= winDuration) {
			celebrate(false);
			winTimer = 0;
		}
	}

	if (clicked) {
		clickTimer += t;	
		//cout << clickTimer << "\n";
		if (clickTimer >= clickCooldown) {
			clicked = false;
			clickTimer = 0;
			createNextFruit();
		}
	}

	Vector3 pointer = { (((float)pointerPos - 250 - (float)(GLdouble(glutGet(GLUT_WINDOW_WIDTH)) / 2)) / 5), 140, -45 };
	if (pointer.x > -85 && pointer.x < -17) {
		dropIndicator->setPos({ (((float)pointerPos - 250 - (float)(GLdouble(glutGet(GLUT_WINDOW_WIDTH)) / 2)) / 5), 85, -50});
		currFruit->setPos(pointer);
		cloud->setOrigin(pointer);
	}


	pfr.updateForces(t);

	while (!genQueue.empty()) {
		combineFruit(genQueue.front().first, genQueue.front().second); genQueue.pop();
	}

	for (auto e = _fruits.begin(); e != _fruits.end();) {
		if ((*e)->getSize() < partType[(*e)->getType()].size * fruitScale) {
			(*e)->setSize((*e)->getSize() + 2.5 * t);
			if ((*e)->getSize() > partType[(*e)->getType()].size * fruitScale)
				(*e)->setSize(partType[(*e)->getType()].size * fruitScale);
		}
		if ((*e)->getPose().p.y > 140.0) {
			lost = true;
			break;
		}
		if (((*e)->getLifespan() != -1 && (*e)->_ls < 0) || outOfBounds(*e) || !(*e)->isAlive() ) {
			if (!lost) {
				(*e)->die();
				rels.erase((*e)->getActor());
				e = _fruits.erase(e);
			}
		}
		else ++e;
	}

	if (lost) {
		lost = false;
		cout << "GAME OVER\n";
		for (auto e = _fruits.begin(); e != _fruits.end();) {
			pfr.deleteParticleRegistry(*e);
			rels.erase((*e)->getActor());
			(*e)->die();
			delete *e;
			e = _fruits.erase(e);
		}
	}
}

void GameSystem::handleMotion(double x)
{
	pointerPos = x;
}

void GameSystem::mouseClick(int button, int state, int x, int y)
{
	if (button == 0 && state == 0 && !shaking && !clicked) {
		clicked = true;

		Fruit* fruit = new Fruit(currFruit, currFruit->getPose().p, currFruit->getMass(),
			CreateShape(PxSphereGeometry(currFruit->getSize())), currFruit->getColor(), Vector3(0.0f, 0.0f, 0.0f));
		pfr.addRegistry(tornado, fruit);
		_fruits.push_back(fruit);
		rels.insert({ fruit->getActor(), fruit });

		currFruit->die();
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
	leftWall = gPhysics->createRigidStatic(PxTransform({ -88.5,80,-50 }));
	PxShape* s = CreateShape(PxBoxGeometry(1.5, 50, 10));
	leftWall->attachShape(*s);
	RenderItem* ri = new RenderItem(s, leftWall, { 0.39,0.24,0.16,1 });
	gScene->addActor(*leftWall);

	rightWall = gPhysics->createRigidStatic(PxTransform({ -11.5,80,-50 }));
	s = CreateShape(PxBoxGeometry(1.5, 50, 10));
	rightWall->attachShape(*s);
	RenderItem* ri2 = new RenderItem(s, rightWall, { 0.39,0.24,0.16,1 });
	gScene->addActor(*rightWall);

	backWall = gPhysics->createRigidStatic(PxTransform({ -50,80,-65 }));
	s = CreateShape(PxBoxGeometry(40, 50, 1.5));
	backWall->attachShape(*s);
	RenderItem* ri3 = new RenderItem(s, backWall, { 0.39,0.24,0.16,1 });
	gScene->addActor(*backWall);

	PxMaterial* mMaterial;
	mMaterial = gPhysics->createMaterial(0.5, 0.5, 0.0);

	topWall = gPhysics->createRigidStatic(PxTransform({ -50,-100,-50 }));
	s = CreateShape(PxBoxGeometry(40, 1.5, 10), mMaterial);
	topWall->attachShape(*s);
	RenderItem* ri4 = new RenderItem(s, topWall, { 0.39,0.24,0.16,1 });
	gScene->addActor(*topWall);
}

Particle* GameSystem::randomFruit()
{
	int f = _uFruit(_mt) + 10;

	Particle* ret = new Particle(partType[f], false);
	ret->setSize(ret->getSize() * fruitScale);

	return ret;
}

void GameSystem::combineFruit(Fruit* fruit1, Fruit* fruit2)
{
	Vector3 newPos = (fruit1->getPose().p + fruit2->getPose().p) / 2;
	//Vector3 newPos = fruit2->getPose().p;

	Particle* nextFruit = new Particle(partType[fruit1->getType() + 1], false);
	nextFruit->setSize(fruit1->getSize());

	ExplosiveForce* makeSpace = new ExplosiveForce(newPos, 1000, (nextFruit->getSize() + nextFruit->getSize() - fruit1->getSize() * fruitScale));

	fruit1->die();
	fruit2->die();
	rels.erase(fruit1->getActor());
	rels.erase(fruit2->getActor());

	for (auto it = _fruits.begin(); it != _fruits.end();) {
		if (*it == fruit1 || *it == fruit2) {
			it = _fruits.erase(it);
		}
		else {
			pfr.addRegistry(makeSpace, *it);
			++it;
		}
	}

	Fruit* genfruit = new Fruit(nextFruit, newPos, nextFruit->getMass(),
		CreateShape(PxSphereGeometry(nextFruit->getSize())), nextFruit->getColor(), Vector3(0.0f, 0.0f, 0.0f));

	_fruits.push_back(genfruit);
	rels.insert({ genfruit->getActor(), genfruit });
	pfr.addRegistry(tornado, genfruit);
	if (genfruit->getType() == _types::WATERMELON) {
		celebrate(true);
	}

	nextFruit->die();

	//return genfruit;
}

void GameSystem::activateFireworks(bool b)
{
	fireWorks1->setActive(b);
	fireWorks2->setActive(b);
}

void GameSystem::shake(bool b)
{	
	shaking = b;
	tornado->setActive(b);
	cloud->setActive(!b);
	currFruit->setVisible(!b);

	if (b) {
		topWall->setGlobalPose(PxTransform({ -50,130,-50 }));
		dropIndicator->setVisible(false);
	}
	else {
		for (auto e : _fruits) {
			e->clearForce();
			e->setVelocity(Vector3(0.0, 0.0, 0.0));
		}
		topWall->setGlobalPose(PxTransform({ -50,30,-50 }));
		dropIndicator->setRenderItem(CreateShape(PxBoxGeometry(0.5, 55, 0.5)), { 0,0,0 }, colorsInfo[WHITE]);
	}
}

void GameSystem::celebrate(bool b)
{
	win = b;
	activateFireworks(b);
}

void GameSystem::lose()
{
	cout << "GAME OVER\n";
	for (auto e : _fruits) {
		onParticleDeath(e);
		_dumpster.push_back(e);
	}
}

void GameSystem::createNextFruit()
{
	currFruit = new Particle(nextFruit);

	nextFruit->die();
	nextFruit = randomFruit();

	Vector3 kPos = keychain->getPose().p;
	keychain->die();
	keychain = new Particle(nextFruit);
	keychain->setPos(kPos);

	pfr.addRegistry(grav, keychain);
	pfr.addRegistry(sf, keychain);
	_particles.push_back(keychain);
}
