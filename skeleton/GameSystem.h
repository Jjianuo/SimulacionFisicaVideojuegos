#pragma once
#include <unordered_map>
#include <queue>
#include "RBSystem.h"
#include "Fruit.h"

class GameSystem : public RBSystem
{
	Particle* currFruit = nullptr;
	Particle* dropIndicator = nullptr;
	UniformParticleGenerator* cloud = nullptr;
	double pointerPos;
	double fruitScale;

	list<Fruit*> _fruits;
	unordered_map<PxActor*, Fruit*> rels;
	queue<pair<Fruit*, Fruit*>> genQueue;
	std::mt19937 _mt;
	std::uniform_real_distribution<double> _uFruit{ 0, 5 };
public:
	GameSystem();
	~GameSystem() { currFruit->die(); };

	virtual void update(double t);
	void handleMotion(double x);
	void mouseClick(int button, int state, int x, int y);
	void onCollision(physx::PxActor* actor1, physx::PxActor* actor2);
	void gameSetup();

	void randomFruit();
	Fruit* combineFruit(Fruit* fruit1, Fruit* fruit2);
};

