#pragma once
#include <list>
#include <iostream>
#include <vector>
#include "Particle.h"
#include "ParticleGenerator.h"
#include "Firework.h"
#include "UniformParticleGenerator.h"
#include "GaussianParticleGenerator.h"
#include "ForceGenerator.h"
#include "GravityForceGenerator.h"
#include "ParticleDragGenerator.h"
#include "WindGenerator.h"
#include "TornadoGenerator.h"
#include "ExplosiveForce.h"
#include "SpringForce.h"
#include "ElasticBandForce.h"
#include "BuoyancyForceGenerator.h"
#include "ParticleForceRegistry.h"

using namespace std;
class ParticleSystem
{
protected:
	list<Particle*> _particles;
	list<Particle*> _dumpster;
	// These are the registred generators(for on demand set generation prob.to 0)
	list<ParticleGenerator*> _pGenerator;

	int payload;
	// This generator is only to shoot the firework!!
	ParticleGenerator* _firework_generator;
	ParticleForceRegistry pfr;

	ParticleGenerator* uniGen;
	Particle* p1;
	//! This is used currently in the Fireworks to spread more Fireworks!
	void onParticleDeath(Particle* p);
	bool outOfBounds(Particle* p);
	double area;
public:
	ParticleSystem();
	~ParticleSystem();

	virtual void update(double t);
	// Method to generate a Firework with the appropiate type
	void generateFirework(unsigned firework_type);
	virtual void generateForce(unsigned type);
	void generateSpringDemo();
	void generateSpringDemo2();
	void generateSlinkyDemo();
	void generateBuoyancyDemo();

	// Gets a particle generator with name...
	ParticleGenerator* getParticleGenerator(const string& n);

	virtual void addGenerator(unsigned type);
	virtual void wipe();
};

