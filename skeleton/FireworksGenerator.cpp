#include "FireworksGenerator.h"

FireworksGenerator::FireworksGenerator(Vector3 origin, Vector3 mean_velocity) : UniformParticleGenerator(origin, mean_velocity)
{
}

FireworksGenerator::FireworksGenerator(Firework* p, Vector3 origin, Vector3 mean_velocity) : UniformParticleGenerator(p, origin, mean_velocity)
{
	_model_particle = p->clone();
	setNParticles(1);
	setGenerationProb(0.01);
}
