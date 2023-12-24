#pragma once
#include "RBSystem.h"

class GameSystem : public RBSystem
{
	Particle* currFruit = nullptr;
	double pointerPos;

	std::mt19937 _mt;
	std::uniform_real_distribution<double> _uFruit{ 0, 5 };
public:
	GameSystem();
	~GameSystem() {};

	virtual void update(double t);
	void handleMotion(double x);
	void gameSetup();
};

