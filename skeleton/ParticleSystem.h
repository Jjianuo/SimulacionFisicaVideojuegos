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
#include "ParticleForceRegistry.h"

using namespace std;
class ParticleSystem
{
	list<Particle*> _particles;
	list<Particle*> _dumpster;
	// These are the registred generators(for on demand set generation prob.to 0)
	list<ParticleGenerator*> _pGenerator;

	int payload;
	// This generator is only to shoot the firework!!
	ParticleGenerator* _firework_generator;
	ParticleForceRegistry pfr;

	UniformParticleGenerator* uniGen;
	Particle* p1;
	//! This is used currently in the Fireworks to spread more Fireworks!
	void onParticleDeath(Particle* p);
	bool outOfBounds(Particle* p);
	double area;
public:
	ParticleSystem();
	~ParticleSystem();

	void update(double t);
	// Method to generate a Firework with the appropiate type
	void generateFirework(unsigned firework_type);
	void generateForce(unsigned type);
	void generateSpringDemo();
	void generateSpringDemo2();
	void generateSlinkyDemo();
	// Gets a particle generator with name...
	ParticleGenerator* getParticleGenerator(const string& n);

	void addGenerator(unsigned type);
};

