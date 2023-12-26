#pragma once
#include "RigidBody.h"

//namespace part {
//	struct FruitInfo {
//		Vector3 mat;
//	};
//
//	enum _types : int {
//		CHERRY,
//		STRAWBERRY,
//		BLACKBERRY,
//		DEKOPON,
//		PERSIMMON,
//		APPLE,
//		PEAR,
//		PEACH,
//		PINEAPPLE,
//		MELON,
//		WATERMELON
//	};
//
//	static ParticleInfo partType[11]{
//		{CHERRY, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 },
//		{ 0.0, 0.0, 0.0 }, 0.2, 0.998, -1, 0.3,
//		colorsInfo[CRIMSON], 1, true, true, nullptr},
//
//		{STRAWBERRY, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 },
//		{ 0.0, 0.0, 0.0 }, 0.4, 0.998, -1, 0.5,
//		colorsInfo[LIGHT_RED], 1, true, true, nullptr},
//
//		{BLACKBERRY, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 },
//		{ 0.0, 0.0, 0.0 }, 0.5, 0.998, -1, 0.8,
//		colorsInfo[PURPLE], 1, true, true, nullptr},
//
//		{DEKOPON, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 },
//		{ 0.0, 0.0, 0.0 }, 1, 0.998, -1, 1,
//		colorsInfo[LIGHT_ORANGE], 1, true, true, nullptr},
//
//		{PERSIMMON, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 },
//		{ 0.0, 0.0, 0.0 }, 1.3, 0.998, -1, 1.3,
//		colorsInfo[ORANGE], 1, true, true, nullptr},
//
//		{APPLE, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 },
//		{ 0.0, 0.0, 0.0 }, 1.8, 0.998, -1, 1.6,
//		colorsInfo[RED], 1, true, true, nullptr},
//
//		{PEAR, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 },
//		{ 0.0, 0.0, 0.0 }, 2, 0.998, -1, 1.9,
//		colorsInfo[LIGHT_YELLOW], 1, true, true, nullptr},
//
//		{PEACH, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 },
//		{ 0.0, 0.0, 0.0 }, 2.3, 0.998, -1, 2.2,
//		colorsInfo[LIGHT_PINK], 1, true, true, nullptr},
//
//		{PINEAPPLE, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 },
//		{ 0.0, 0.0, 0.0 }, 2.8, 0.998, -1, 2.5,
//		colorsInfo[YELLOW], 1, true, true, nullptr},
//
//		{MELON, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 },
//		{ 0.0, 0.0, 0.0 }, 3, 0.998, -1, 2.8,
//		colorsInfo[LIGHT_GREEN], 1, true, true, nullptr},
//
//		{WATERMELON, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 },
//		{ 0.0, 0.0, 0.0 }, 3.3, 0.998, -1, 3.0,
//		colorsInfo[GREEN], 1, true, true, nullptr},
//	}
//
//	static FruitInfo fruitType[11]{
//		{}
//	}
//}

using namespace part;

class Fruit : public RigidBody
{
public:
	Fruit(Vector3 pos, double m, PxShape* s, PxVec4 c, PxMaterial* mat, Vector3 inertiaTensor = { -1,-1,-1 });
	Fruit(Vector3 pos, double m, PxShape* s, PxVec4 c, Vector3 mat, Vector3 inertiaTensor = { -1,-1,-1 });
	Fruit(Particle* p, Vector3 pos, double m, PxShape* s, PxVec4 c, Vector3 mat, Vector3 inertiaTensor = { -1,-1,-1 });

	PxActor* getActor();
	virtual void setPos(PxVec3 p);
};

