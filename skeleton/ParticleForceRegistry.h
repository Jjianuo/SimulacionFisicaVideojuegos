#pragma once
#include <unordered_map>
#include <unordered_set>
#include <list>
#include "ForceGenerator.h"
#include "ParticleGenerator.h"

using namespace std;
using particulas = unordered_map<Particle*, unordered_set<ForceGenerator*>>;

class ParticleForceRegistry 
{
	unordered_map<ForceGenerator*, pair<unordered_set<Particle*>, unordered_set<ParticleGenerator*>>> gens;
	unordered_map<ParticleGenerator*, unordered_set<ForceGenerator*>> particleGenerators;
	particulas particles;
	list<ForceGenerator*> killList;
public:
	ParticleForceRegistry() {};

	void updateForces(double t) {
		for (auto& g : gens) {
			g.first->updateTime(t);
			for (auto& p : g.second.first) { //p es la particula
				g.first->updateForce(p, t);
			}
		}
		for (auto& e : killList) {
			deleteForce(e);
		}
		killList.clear();
	}

	void addRegistry(ForceGenerator* fg, Particle* p) {
		gens[fg].first.insert(p);
		particles[p].insert(fg);
	}

	void addPaticleGenerator(ForceGenerator* fg, ParticleGenerator* pg) {
		particleGenerators[pg].insert(fg);
		gens[fg].second.insert(pg);
	}

	void deleteParticleRegistry(Particle* p) { 
		if (particles.count(p) > 0) {
			for (auto& e : particles[p]) {
				gens[e].first.erase(p);
			}
			particles.erase(p);
		}
	}

	void deleteForce(ForceGenerator* fg) {
		if (gens.count(fg) > 0) {
			for (auto& e : gens[fg].second) {
				particleGenerators[e].erase(fg);
			}
			gens.erase(fg);
		}
	}

	void reset() {
		gens.clear();
		particleGenerators.clear();
	}

	inline unordered_map<ParticleGenerator*, unordered_set<ForceGenerator*>>& getPartGens() { return particleGenerators; }
	inline unordered_map<ForceGenerator*, pair<unordered_set<Particle*>, unordered_set<ParticleGenerator*>>> getForceGens() { return gens; }
};

