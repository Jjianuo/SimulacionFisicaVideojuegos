#include "SceneManager.h"
#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"

#include <iostream>

struct Text
{
	std::string text;
	Vector3 color;
	int x; int y;
	void* font;
};

int text = 2;
int textColour = 0;
std::vector<std::string> display_texts = { "GAME OVER", "YOU WON", "" };
std::vector<physx::PxVec3> display_text_colours = { physx::PxVec3(1.0, 0.0, 0.0), physx::PxVec3(0.0, 1.0, 0.0) };
int score = 0;
std::string scoreString = "0";

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation* gFoundation = nullptr;
PxPhysics* gPhysics = nullptr;
PxSceneDesc* sceneDesc = nullptr;

PxMaterial* gMaterial = nullptr;

PxPvd* gPvd = nullptr;

PxDefaultCpuDispatcher* gDispatcher = nullptr;
PxScene* gScene = nullptr;
ContactReportCallback gContactReportCallback;

using namespace physx;

SceneManager* scene;

// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	scene = new SceneManager();
}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

	scene->update(t);
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	delete scene;
}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	switch(toupper(key))
	{
	case ' ':
	{
		break;
	}
	default:
		break;
	}

	scene->keyPress(key, camera);
}

void handleMotion(int x, int y) {
	scene->handleMotion(x, y);
};

void mouseClick(int button, int state, int x, int y) {
	scene->mouseClick(button, state, x, y);
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	//PX_UNUSED(actor1);
	//PX_UNUSED(actor2);

	scene->onCollision(actor1, actor2);
}

void updateScore() {
	scoreString = to_string(scene->getScore());
	text = scene->getGameState();
}

int main(int, const char*const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for(PxU32 i=0; i<frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}