#include "Firework.h"
#include <iostream>

Firework::Firework(bool v, Vector3 pos, Vector3 Vel, Vector3 Acc, double m, double damp, double ls, Vector4 c, unsigned t, int gen)
	: Particle(false, { 0.0, 0.0, 0.0 }, { 0.0, 25.0, 0.0 }, Acc, m, damp, ls, m, c, t, gen)
{
	_mt = std::mt19937{ std::random_device()() };
	if (pInfo.visible)
		pInfo.renderItem = new RenderItem(CreateShape(PxSphereGeometry(m)), &pInfo.pose, c);
	else
		pInfo.renderItem = nullptr;
}

Firework::Firework(ParticleInfo pInf) : Particle(pInf, false)
{
	_mt = std::mt19937{ std::random_device()() };
	pInfo = pInf;

	if (pInfo.visible)
		pInfo.renderItem = new RenderItem(CreateShape(PxSphereGeometry(pInfo.mass)), &pInfo.pose, pInfo.color);
	else
		pInfo.renderItem = nullptr;
}


std::list<Particle*> Firework::explode()
{
	std::list<Particle*> ret;
	for (auto e : _gens) {
		e->setOrigin(Vector3(pInfo.pose.p));
		//std::cout << pInfo.pose.p.x << " " << pInfo.pose.p.y << " " << pInfo.pose.p.z << "\n";
		Vector3 v = Vector3(_u(_mt), _u(_mt), _u(_mt)) * 20;
		e->setMeanVelocity(v);
		e->setMeanDuration(pInfo.lifespan);

		for (auto g : e->generateParticles()) {
			g->setGeneration(pInfo._generation - 1);
			g->changeLifespan(pInfo.lifespan);
			ret.push_back(g);
		}
	}
	return ret;
}

void Firework::addGenerator(std::shared_ptr<ParticleGenerator> p)
{
	//_gens.push_back(std::make_shared<ParticleGenerator>(&p));
	_gens.push_back(p);
}

Firework* Firework::clone() const
{
	Firework* aux = new Firework(pInfo);
	aux->_gens = _gens;
	return aux;
}
