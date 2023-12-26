#include "ParticleSystem.h"

void ParticleSystem::onParticleDeath(Particle* p)
{
	switch (p->getType())
	{
	case FIREWORK: {
		for (auto e : static_cast<Firework*>(p)->explode()) {
			if (e->getGeneration() > -1) {
				e->show();
				_particles.push_back(e);
			}
		}
	}
	default:
		break;
	}
}

bool ParticleSystem::outOfBounds(Particle* p)
{
	if (p->getPose().p.magnitude() > area)
		return true;
	return false;
}

ParticleSystem::ParticleSystem() : area(170)
{
}

ParticleSystem::~ParticleSystem()
{
	wipe();
}

void ParticleSystem::update(double t)
{
	for (auto g : _pGenerator) {
		auto partGens = pfr.getPartGens();
		for (auto pg : g->generateParticles()) {
			for (auto& e : partGens[g]) {
				pfr.addRegistry(e, pg);
			}
			_particles.push_back(pg);
		}
	}
	pfr.updateForces(t);
	for (auto g : pfr.getForceGens()) {
		if (!g.first->updateTime(t)) {
			pfr.deleteForce(g.first);
		}
	}
	for (auto e : _particles) {
		e->integrate(t);
		if (e->getLifespan() != -1 || !e->isAlive()) {
			e->_ls -= t;
			if (e->_ls < 0 || outOfBounds(e)) {
				onParticleDeath(e);

				_dumpster.push_back(e);
			}
		}
	}

	for (auto d : _dumpster) {
		pfr.deleteParticleRegistry(d);
		_particles.remove(d);
		d->die();
		delete d;
	}
	_dumpster.clear();
}

void ParticleSystem::generateFirework(unsigned firework_type)
{
	switch (firework_type)
	{
	case 0: { //??
		Firework* temp = new Firework(partType[FIREWORK]);
		temp->setPos(Vector3(0.0, 0.0, 0.0));
		temp->setAcceleration(temp->getAcceleration() + Vector3{ 0.0, -9.8, 0.0 });
		temp->setGeneration(2);


		std::shared_ptr<ParticleGenerator> auxGen1(new GaussianParticleGenerator());
		Firework* aux1 = new Firework(partType[CHERRY_BLOSSOM]);
		aux1->setMass(3);
		auxGen1->setParticle(aux1);
		auxGen1->setRandomLifespan(true);
		auxGen1->setNParticles(5);

		std::shared_ptr<ParticleGenerator> auxGen2(new GaussianParticleGenerator());
		Firework* aux2 = new Firework(partType[FIREWORK]);
		aux2->setColor(colorsInfo[LIGHT_BLUE]);
		aux2->setMass(3);
		aux2->addGenerator(auxGen1);
		auxGen2->setParticle(aux2);
		auxGen2->setRandomLifespan(true);
		auxGen2->setNParticles(7);


		temp->addGenerator(auxGen1);
		temp->addGenerator(auxGen2);
 
		_particles.push_back(temp);
		delete aux1;
		delete aux2;
		break;
	}
	case 1: { //RAINBOW
		Firework* temp = new Firework(partType[FIREWORK]);
		temp->setGeneration(2);
		temp->setPos(Vector3(0.0, 0.0, 0.0));
		temp->setAcceleration(temp->getAcceleration() + Vector3{ 0.0, -9.8, 0.0 });

		for (int i = 0; i < 7; ++i) {
			std::shared_ptr<ParticleGenerator> auxGen1(new GaussianParticleGenerator());
			Firework* aux1 = new Firework(partType[DEFAULT]);
			aux1->setColor(colorsInfo[RED + i]);
			auxGen1->setParticle(aux1);
			auxGen1->setNParticles(2);
			auxGen1->setRandomLifespan(true);
			temp->addGenerator(auxGen1);
			delete aux1;
		}

		_particles.push_back(temp);
		break;
	}
	case 2: { //LAME 
		Firework* temp = new Firework(partType[FIREWORK]);
		temp->setGeneration(4);
		temp->setPos(Vector3(0.0, 0.0, 0.0));
		temp->setAcceleration(temp->getAcceleration() + Vector3 { 0.0, -9.8, 0.0 });

		std::shared_ptr<ParticleGenerator> auxGen1(new GaussianParticleGenerator());
		Firework* aux1 = new Firework(partType[DEFAULT]);
		aux1->setColor(colorsInfo[RED]);
		auxGen1->setParticle(aux1);
		auxGen1->setNParticles(100);
		auxGen1->setRandomLifespan(true);
		temp->addGenerator(auxGen1);
		delete aux1;

		_particles.push_back(temp);
		break;
	}
	case 3: { //wtfd
		Firework* temp = new Firework(partType[FIREWORK]);
		temp->setGeneration(4);
		temp->setPos(Vector3(0.0, 0.0, 0.0));
		temp->setAcceleration(temp->getAcceleration() + Vector3{ 0.0, -9.8, 0.0 });

		std::shared_ptr<ParticleGenerator> auxGen1(new GaussianParticleGenerator()); //genera aux1234
		std::shared_ptr<ParticleGenerator> auxGen2(new GaussianParticleGenerator()); //genera aux234
		std::shared_ptr<ParticleGenerator> auxGen3(new GaussianParticleGenerator()); //genera aux34
		std::shared_ptr<ParticleGenerator> auxGen4(new GaussianParticleGenerator()); //genera aux4

		Firework* aux1 = new Firework(partType[FIREWORK]);
		aux1->setColor(colorsInfo[RED]);
		Firework* aux2 = new Firework(partType[FIREWORK]);
		aux2->setColor(colorsInfo[LIGHT_BLUE]);
		Firework* aux3 = new Firework(partType[FIREWORK]); //aux3 genera particulas aux4
		aux3->setColor(colorsInfo[GREEN]);
		Firework* aux4 = new Firework(partType[DEFAULT]); //aux4 genera particulas normales

		auxGen1->setNParticles(4);
		auxGen2->setNParticles(4);
		auxGen3->setNParticles(4);
		auxGen4->setNParticles(4);
		auxGen1->setRandomLifespan(true);
		auxGen2->setRandomLifespan(true);
		auxGen3->setRandomLifespan(true);
		auxGen4->setRandomLifespan(true);

		aux4->setColor(colorsInfo[LIGHT_PINK]);
		auxGen4->setParticle(aux4);

		aux3->addGenerator(auxGen4);
		auxGen3->setParticle(aux3);

		aux2->addGenerator(auxGen3);
		aux2->addGenerator(auxGen4);
		auxGen2->setParticle(aux2);

		aux1->addGenerator(auxGen2);
		aux1->addGenerator(auxGen3);
		aux1->addGenerator(auxGen4);
		auxGen1->setParticle(aux1);

		temp->addGenerator(auxGen1);
		temp->addGenerator(auxGen2);
		temp->addGenerator(auxGen3);
		temp->addGenerator(auxGen4);

		_particles.push_back(temp);

		delete aux1;
		delete aux2;
		delete aux3;
		delete aux4;
		break;
	}
	default:
		break;
	}
}

void ParticleSystem::generateForce(unsigned type)
{
	switch (type)
	{
	case 0:
	{
		ExplosiveForce* aux = new ExplosiveForce();
		aux->setOrigin({ 20.0f, 15.0f, 20.0f });
		pfr.addPaticleGenerator(aux, uniGen);
	}
	case 1:
	{
		ExplosiveForce* aux = new ExplosiveForce();
		aux->setOrigin({ -3.0f, 10.0f, 0.0f });
		pfr.addRegistry(aux, p1);
	}
	default:
		break;
	}
}

void ParticleSystem::generateSpringDemo()
{
	p1 = new Particle(true, {-10.0, 10.0,0.0}, {0.0,0.0,0.0}, {0.0,0.0,0.0}, 1);
	Particle* p2 = new Particle(true, {10.0, 10.0,0.0}, {0.0,0.0,0.0}, {0.0,0.0,0.0}, 9999999999);
	p1->changeLifespan(99);
	p2->changeLifespan(99);
	p2->setShape(PxGeometryType::eBOX);

	SpringForce* f1 = new SpringForce(1, 10, p2);
	SpringForce* f2 = new SpringForce(1, 10, p1);
	GravityForceGenerator* g1 = new GravityForceGenerator({0,-9.8,0});
	pfr.addRegistry(g1, p1);
	pfr.addRegistry(f1, p1);
	pfr.addRegistry(f2, p2);
	_particles.push_back(p1);
	_particles.push_back(p2);
}

void ParticleSystem::generateSpringDemo2()
{
	p1 = new Particle(true, { -5.0, 10.0,0.0 }, { 0.0,0.0,0.0 }, { 0.0,0.0,0.0 }, 1);
	Particle* p2 = new Particle(false, { 5.0, 10.0,0.0 }, { 0.0,0.0,0.0 }, { 0.0,0.0,0.0 }, 1);
	p2->setColor(colorsInfo[RED]);
	p1->changeLifespan(-1);
	p2->changeLifespan(-1);

	TornadoGenerator* aux = new TornadoGenerator(3);
	aux->setOrigin({ -1.0f, -20.0f, 0.0 });
	pfr.addRegistry(aux, p1);
	pfr.addRegistry(aux, p2);

	SpringForce* f1 = new SpringForce(1, 5, p2);
	SpringForce* f2 = new SpringForce(1, 5, p1);

	//ElasticBandForce* f1 = new ElasticBandForce(1, 10, p2);
	//ElasticBandForce* f2 = new ElasticBandForce(1, 10, p1);

	pfr.addRegistry(f1, p1);
	pfr.addRegistry(f2, p2);
	_particles.push_back(p1);
	_particles.push_back(p2);
}

void ParticleSystem::generateSlinkyDemo()
{
	Particle* p1 = new Particle(partType[ICE]);
	Particle* p2 = new Particle(partType[FIRE]);
	Particle* p3 = new Particle(partType[WATER]);
	Particle* p4 = new Particle(partType[BULLET]);
	Particle* p5 = new Particle(partType[MIST]);
	Particle* p6 = new Particle(partType[DEFAULT]);

	p1->setPos({ 0,35,0 });
	p2->setPos({ 0,25,0 });
	p3->setPos({ 0,15,0 });
	p4->setPos({ 0,10,0 });
	p5->setPos({ 0,5,0 });
	p6->setPos({ 0,-20,0 });

	p1->changeLifespan(-1);
	p2->changeLifespan(-1);
	p3->changeLifespan(-1);
	p4->changeLifespan(-1);
	p5->changeLifespan(-1);
	p6->changeLifespan(-1);

	ElasticBandForce* f1 = new ElasticBandForce(1, 1, p2);
	ElasticBandForce* f2 = new ElasticBandForce(1, 20, p3);
	ElasticBandForce* f3 = new ElasticBandForce(1, 5, p4);
	ElasticBandForce* f4 = new ElasticBandForce(1, 2, p5);
	ElasticBandForce* f5 = new ElasticBandForce(1, 12, p6);

	GravityForceGenerator* g = new GravityForceGenerator({ 0,-9.8,0 });

	pfr.addRegistry(f1, p1);
	pfr.addRegistry(f2, p2);
	pfr.addRegistry(f3, p3);
	pfr.addRegistry(f4, p4);
	pfr.addRegistry(f5, p5);

	pfr.addRegistry(g, p1);
	pfr.addRegistry(g, p2);
	pfr.addRegistry(g, p3);
	pfr.addRegistry(g, p4);
	pfr.addRegistry(g, p5);
	pfr.addRegistry(g, p6);

	_particles.push_back(p1);
	_particles.push_back(p2);
	_particles.push_back(p3);
	_particles.push_back(p4);
	_particles.push_back(p5);
	_particles.push_back(p6);
}

void ParticleSystem::generateBuoyancyDemo()
{
	Particle* water = new Particle(partType[WATER], false);
	water->setPos(Vector3( 0, 0, 0 ));
	water->setRenderItem(CreateShape(PxBoxGeometry(50, 0.1, 50)), water->getPose().p, water->getColor());
	water->changeLifespan(-1);

	Particle* p2 = new Particle(false, { 0.0, 10.0,0.0 }, { 0.0,0.0,0.0 }, { 0.0,0.0,0.0 }, 10, 0.0499);
	p2->changeLifespan(-1);
	double cubeSize = 2;
	p2->setRenderItem(CreateShape(PxBoxGeometry(cubeSize, cubeSize, cubeSize)), p2->getPose().p, colorsInfo[RED]);

	float grav = 9.8f;
	GravityForceGenerator* g = new GravityForceGenerator({ 0,-grav,0 });
	BuoyancyForceGenerator* bg = new BuoyancyForceGenerator(water, cubeSize, pow(cubeSize, 3), 1000, grav);
	pfr.addRegistry(g, p2);
	pfr.addRegistry(bg, p2);

	_particles.push_back(water);
	_particles.push_back(p2);
}

void ParticleSystem::addGenerator(unsigned type) {
	switch (type)
	{
	case 0: {
		UniformParticleGenerator* mistGen = new UniformParticleGenerator();
		Particle* mistParticle = new Particle(partType[MIST]);
		mistGen->setParticle(mistParticle);
		mistGen->setOffset({ 50.0f, 50.0f, 50.0f });
		mistGen->setMeanVelocity({ 0.1, 0.1, 0.1 });
		_pGenerator.push_back(mistGen);
		delete mistParticle;
		break;
	}
	case 1: {
		GaussianParticleGenerator* cherryGen = new GaussianParticleGenerator();
		Particle* cherryParticle = new Particle(partType[CHERRY_BLOSSOM]);
		cherryGen->setParticle(cherryParticle);
		cherryGen->setOffset({ 50.0f, 50.0f, 50.0f });
		cherryGen->setMeanVelocity({ 0.05, 0.00, 0.05 });
		_pGenerator.push_back(cherryGen);
		delete cherryParticle;
		break;
	}
	case 2: {
		UniformParticleGenerator* rainGen = new UniformParticleGenerator();
		Particle* waterParticle = new Particle(partType[WATER]);
		rainGen->setParticle(waterParticle);
		rainGen->setOffset({ 50.0f, 5.0f, 50.0f });
		rainGen->setMeanVelocity({ 0.05, 0.00, 0.05 });
		rainGen->setOrigin({ 00.0f, 100.0f, 0.0f });
		_pGenerator.push_back(rainGen);
		delete waterParticle;
		break;
	}
	case 3: {
		uniGen = new UniformParticleGenerator();
		Particle* auxParticle = new Particle(partType[ICE], true);
		auxParticle->setSize(0.2);
		auxParticle->setMass(10);
		uniGen->setParticle(auxParticle);
		uniGen->setMeanVelocity({ 3, 3, 3 });
		uniGen->setOrigin({ 20.0f, 20.0f, 20.0f });
		uniGen->setOffset({ 3,3,3 });
		pfr.addPaticleGenerator(new GravityForceGenerator({ 0.0, -9.8, 0.0, }), uniGen);
		//WindGenerator* aux = new WindGenerator();
		//aux->setOrigin({ 20.0f, 20.0f, 20.0f });
		//pfr.addPaticleGenerator(aux, uniGen);

		_pGenerator.push_back(uniGen);

		delete auxParticle;
		break;
	}
	case 4: {
		GaussianParticleGenerator* gausGen = new GaussianParticleGenerator();
		Particle* auxParticle2 = new Particle(partType[ICE]);
		auxParticle2->setMass(200);
		auxParticle2->setSize(1);
		gausGen->setParticle(auxParticle2);
		gausGen->setMeanVelocity({ 3, 3, 3 });
		gausGen->setOrigin({ -20.0f, 20.0f, 20.0f });
		pfr.addPaticleGenerator(new GravityForceGenerator({ 0.0, -9.8, 0.0, }), gausGen);
		TornadoGenerator* aux = new TornadoGenerator(3);
		aux->setArea(70.0);
		aux->setOrigin({ -20.0f, 20.0f, 20.0f });
		pfr.addPaticleGenerator(aux, gausGen);

		_pGenerator.push_back(gausGen);

		delete auxParticle2;
		break;
	}
	case 5: {
		GaussianParticleGenerator* gausGen = new GaussianParticleGenerator();
		Particle* auxParticle2 = new Particle(partType[ICE]);
		auxParticle2->setMass(200);
		auxParticle2->setSize(1);
		gausGen->setParticle(auxParticle2);
		gausGen->setMeanVelocity({ 3, 3, 3 });
		gausGen->setOrigin({ -20.0f, 20.0f, -20.0f });
		pfr.addPaticleGenerator(new GravityForceGenerator({ 0.0, -9.8, 0.0, }), gausGen);
		WindGenerator* aux = new WindGenerator();
		aux->setArea(70.0);
		aux->setOrigin({ -20.0f, -20.0f, -20.0f });
		pfr.addPaticleGenerator(aux, gausGen);

		_pGenerator.push_back(gausGen);

		delete auxParticle2;
		break;
	}
	case 9: { //hose
		UniformParticleGenerator* hoseGen = new UniformParticleGenerator();
		Particle* waterParticle = new Particle(partType[WATER]);
		hoseGen->setParticle(waterParticle);
		hoseGen->setMinVar(0);
		hoseGen->setMaxVar(0.4f);
		hoseGen->setMeanVelocity({ 100, 10, -10 });
		hoseGen->setOrigin({ 20.0f, 20.0f, 20.0f });
		_pGenerator.push_back(hoseGen);
		delete waterParticle;
		break;
	}
	default:
		break;
	}
}

void ParticleSystem::wipe()
{
	for (auto pg : _pGenerator)
		delete pg;
	for (auto& p : _particles) {
		p->die();
		delete p;
	}
	_pGenerator.clear();
	_particles.clear();
}
