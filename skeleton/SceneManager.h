#pragma once
#include <vector>
#include <iostream>
#include <PxScene.h>

#include "Particle.h"
#include "Shooter.h"
#include "callbacks.hpp"
#include "ParticleSystem.h"
#include "RBSystem.h"
#include "GameSystem.h"

using namespace physx;
using namespace std;

extern PxDefaultAllocator		gAllocator;
extern PxDefaultErrorCallback	gErrorCallback;

extern PxFoundation* gFoundation;
extern PxPhysics* gPhysics;
extern PxSceneDesc* sceneDesc;

extern PxMaterial* gMaterial;

extern PxPvd* gPvd;

extern PxDefaultCpuDispatcher* gDispatcher;
extern PxScene* gScene;
extern ContactReportCallback gContactReportCallback;

class SceneManager
{
private:
	int currScene;
	Shooter* shoot = nullptr;
	ParticleSystem* pSys = nullptr;
	RBSystem* rbSys = nullptr;
	GameSystem* gameSys = nullptr;
	
public:
	SceneManager();
	~SceneManager();
	void update(double t);
	void handleMotion(double x, double y);
	void mouseClick(int button, int state, int x, int y);
	void keyPress(unsigned char key, const PxTransform& camera);
	void onCollision(physx::PxActor* actor1, physx::PxActor* actor2);
	void changeScene(int scene);
	void clear();
	int getScore();
	int getGameState();
};

