#pragma once
#include <time.h>
#include <list>
#include <random>
#include "Particle.h"
#include "core.hpp"


class ParticleGenerator
{
protected:
	ParticleGenerator() {};
	ParticleGenerator(Particle* p) {};

	int _n_particles = 1; // Number of particles for each generateParticles call(TODO: add randomness ? ? )
	double _generation_prob = 1.0; // IF 1.0 --> always produces particles
	ParticleInfo _model_particle;
	Vector3 _origin, _mean_velocity;
	Vector3 offset = { 0.0, 0.0, 0.0 };
	float minVar = -1, maxVar = 1;
	std::mt19937 _mt;
	std::uniform_real_distribution<float> _u{ 0,1 };
	std::string _name;
	bool randomLifespan = false;
	int randomLifespanLimits;
	int minLifespan = 1;
	bool active = true;

public:
	~ParticleGenerator() {  };

	virtual std::list<Particle*> generateParticles() {
		std::list<Particle*> ret;
		if (active && _u(_mt) <= _generation_prob) {
			for (int i = 0; i < _n_particles; ++i) {
				Particle* p = new Particle(_model_particle, true);
				p->setPos(_origin + (getRandomDist() * offset));
				p->setVelocity(getRandomDist() * _mean_velocity);
				if (randomLifespan) {
					p->changeLifespan((_u(_mt) * randomLifespanLimits) + minLifespan);
				}

				ret.push_back(p);
			}
		}
		return ret;
	};

	virtual void setVars() = 0;
	inline void setOrigin(const Vector3& p) { _origin = p; }
	inline const Vector3& getOrigin() { return _origin; }
	inline void setOffset(const Vector3& f) { offset = f; }
	inline void setMeanVelocity(const Vector3& v) {
		_mean_velocity = v;
	}
	inline Vector3 getMeanVelocity() const {
		return _mean_velocity;
	}
	inline void setMeanDuration(double new_duration) {
		_model_particle.lifespan = new_duration;
	}
	//! @brief --> sets the particle, including its type, lifetime and mean positionsand velocities
	inline void setParticle(Particle* p, bool modify_pos_vel = true) {
		_model_particle = p->getPInfo();
		if (modify_pos_vel) {
			_origin = p->getPose().p;
			_mean_velocity = p->getVelocity();
		}
	}

	virtual Vector3 getRandomDist() = 0;

	inline void setNParticles(int n_p) { _n_particles = n_p; }

	inline void setGenerationProb(double p) { _generation_prob = p; }

	inline void setDistribution(std::uniform_real_distribution<float> d) { _u = d; }

	inline void setRandomLifespan(bool b) { randomLifespan = b; }

	inline void setRandomLifespanLimits(int ls) { randomLifespanLimits = ls; }

	inline void setMinVar(float i) { minVar = i; setVars(); }

	inline void setMaxVar(float i) { maxVar = i; setVars(); }

	inline void setActive(bool b) { active = b; }
};

