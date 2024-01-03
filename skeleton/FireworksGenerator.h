#pragma once
#include "UniformParticleGenerator.h"
#include "Firework.h"
#

class FireworksGenerator : public UniformParticleGenerator
{
	Firework* _model_particle;
public:
	FireworksGenerator(Vector3 origin = { 0.0, 0.0, 0.0 }, Vector3 mean_velocity = { 0.0, 0.0, 0.0 });
	FireworksGenerator(Firework* p, Vector3 origin = { 0.0, 0.0, 0.0 }, Vector3 mean_velocity = { 0.0, 0.0, 0.0 });
	~FireworksGenerator();

	virtual std::list<Particle*> generateParticles() {
		std::list<Particle*> ret;
		if (active && _u(_mt) <= _generation_prob) {
			for (int i = 0; i < _n_particles; ++i) {
				Vector3 pos = _origin;
				Firework* p = _model_particle->clone();
				p->setPos(pos);

				ret.push_back(p);
			}
		}
		return ret;
	};

	inline void setParticle(Firework* p, bool modify_pos_vel = true) {
		_model_particle = p->clone();
		if (modify_pos_vel) {
			_origin = p->getPose().p;
			_mean_velocity = p->getVelocity();
		}
	}
};

