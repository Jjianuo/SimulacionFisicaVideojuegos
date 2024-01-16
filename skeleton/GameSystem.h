#pragma once
#include <unordered_map>
#include <queue>
#include "RBSystem.h"
#include "Fruit.h"
#include "FireworksGenerator.h"
#include "SquishedTornadoGenerator.h"

class GameSystem : public RBSystem
{
	Particle* currFruit = nullptr;
	Particle* keychain = nullptr;
	Particle* keychainAux = nullptr;
	Particle* nextFruit = nullptr;
	Particle* dropIndicator = nullptr;
	UniformParticleGenerator* cloud = nullptr;
	FireworksGenerator* fireWorks1 = nullptr;
	FireworksGenerator* fireWorks2 = nullptr;
	PxRigidStatic* leftWall = nullptr;
	PxRigidStatic* rightWall = nullptr;
	PxRigidStatic* backWall = nullptr;
	PxRigidStatic* topWall = nullptr;
	SquishedTornadoGenerator* tornado = nullptr;
	SpringForce* sf = nullptr;
	GravityForceGenerator* grav = nullptr;
	double pointerPos;
	double fruitScale;

	list<Fruit*> _fruits;
	unordered_map<PxActor*, Fruit*> rels;
	queue<pair<Fruit*, Fruit*>> genQueue;
	std::mt19937 _mt;
	std::uniform_real_distribution<double> _uFruit{ 0, 5 };

	bool clicked = false;
	double clickTimer = 0.0;
	double clickCooldown = 1.0;

	Firework* createModelFirework();
	bool shaking = false;
	double timer = 0.0;
	double shakeDuration = 5.0;

	bool win = false;
	double winTimer = 0.0;
	double winDuration = 3.0;

	bool lost = false;
	double lostTimer = 0.0;
	double lostDuration = 3.0;

	vector<int> points = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
	int score = 0;
	int gameState = 2;
public:
	GameSystem();
	~GameSystem();

	virtual void update(double t);
	void handleMotion(double x);
	void mouseClick(int button, int state, int x, int y);
	void onCollision(physx::PxActor* actor1, physx::PxActor* actor2);
	void gameSetup();

	Particle* randomFruit();
	void combineFruit(Fruit* fruit1, Fruit* fruit2);

	void activateFireworks(bool b);
	void shake(bool b);
	void celebrate(bool b);
	void lose();
	void createNextFruit();
	inline int getScore() { return score; }
	inline int getGameState() { return gameState; }
};

