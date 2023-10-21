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

	int _n_particles = 1; // Number of particles for each generateParticles call(TODO: add randomness ? ? )
	double _generation_prob = 1.0; // IF 1.0 --> always produces particles
	Particle* _model_particle = nullptr; // Has the attributes of the particle that will be generated!(damping, lifetime, etc.)
	Vector3 _origin, _mean_velocity;
	std::mt19937 _mt;
	std::uniform_real_distribution<float> _u{ 0,1 };
	std::string _name;


public:
	~ParticleGenerator() { delete _model_particle; };
	virtual std::list<Particle*> generateParticles() = 0;
	inline void setOrigin(const Vector3& p) { _origin = p; }
	inline void setMeanVelocity(const Vector3& v) {
		_mean_velocity = v;
	}
	inline Vector3 getMeanVelocity() const {
		return _mean_velocity;
	}
	inline void setMeanDuration(double new_duration) {
		_model_particle->setLifespan(new_duration);
	}
	//! @brief --> sets the particle, including its type, lifetime and mean positionsand velocities
	inline void setParticle(Particle* p, bool modify_pos_vel = true) {
		if(_model_particle != p) delete _model_particle;
		_model_particle = p->clone();
		if (modify_pos_vel) {
			_origin = p->getPose().p;
			_mean_velocity = p->getVelocity();
		}
	}
	inline void setNParticles(int n_p) { _n_particles = n_p; }

	inline void setGenerationProb(double p) { _generation_prob = p; };

	inline void setDistribution(std::uniform_real_distribution<float> d) { _u = d; };
};
