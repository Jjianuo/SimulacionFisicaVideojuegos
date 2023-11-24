#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"

using namespace physx;

namespace part {
	const int nColors = 11;
	const int nTypes = 10;

	enum _colors : int {
		GRAY,
		RED,
		ORANGE,
		YELLOW,
		GREEN,
		LIGHT_BLUE,
		BLUE,
		PURPLE,
		PINK,
		BLACK,
		WHITE
	};

	enum _shape : int {
		SPHERE,
		CUBE
	};

	static Vector4 colorsInfo[nColors] = {
		{0.2, 0.2, 0.2, 1.0},//gray
		{1.0, 0.0, 0.0, 1.0},//red
		{1.0, 0.37, 0.12, 1.0},//orange
		{1.0, 1.0, 0.0, 1.0},//yellow
		{0.0, 1.0, 0.0, 1.0},//green
		{0.65, 0.78, 0.9, 1.0},//light blue
		{0.0, 0.0, 1.0, 1.0},//blue
		{0.19, 0.1, 0.2, 1.0},//purple
		{1.0, 0.82, 0.86, 1.0},//pink
		{0.0, 0.0, 0.0, 1.0},//black
		{1.0, 1.0, 1.0, 1.0}//white
	};

	enum _types : int {
		DEFAULT,
		BULLET,
		FIREWORK,
		CHERRY_BLOSSOM,
		MIST,
		ICE,
		WATER,
		FIRE,
		LIGHT,
		DARK
	};

	struct ParticleInfo {
		int _type;
		PxTransform pose;
		Vector3 velocity;
		Vector3 acceleration;
		double mass;
		double damping;
		double lifespan;
		double size;
		Vector4 color;
		int _generation;

		bool visible;
		bool alive;
		RenderItem* renderItem;
	};

	static ParticleInfo partType[nTypes] = {
		{DEFAULT, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 },
		{ 0.0, 0.0, 0.0 }, 2, 0.998, 5, 2,
		colorsInfo[GRAY], 1, false, true, nullptr},

		{BULLET, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 },
		{ 0.0, 0.0, 0.0 }, 1, 0.998, 3, 1,
		colorsInfo[BLACK], 1, true, true, nullptr},

		{FIREWORK, { 0.0, 0.0, 0.0 }, { 0.0, 55.0, 0.0 },
		{ 0.0, 0.0, 0.0 }, 0.8, 0.998, 2, 0.8,
		colorsInfo[WHITE], 3, true, true, nullptr},

		{CHERRY_BLOSSOM, { 0.0, 0.0, 0.0 }, { 0.2, 0.0, -0.2 },
		{ 0.0, 9.8, -0.01 }, 0.1, 0.998, 10, 0.1,
		colorsInfo[PINK], 1, true, true, nullptr},

		{MIST, { 0.0, 0.0, 0.0 }, { 0.1, 0.1, -0.1 },
		{ 0.1, 9.8, -0.01 }, 1, 0.998, 10, 1,
		colorsInfo[GRAY], 1, true, true, nullptr},

		{ICE, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 },
		{ 0.0, 0.0, 0.0 }, 1, 0.998, 10, 1,
		colorsInfo[LIGHT_BLUE], 1, true, true, nullptr},

		{WATER, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 1.0 },
		{ 0.0, 0.0, 0.0 }, 1, 0.998, 10, 1,
		colorsInfo[BLUE], 1, true, true, nullptr},
		
		{FIRE, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 1.0 },
		{ 0.0, 0.0, 0.0 }, 0.5, 0.998, 10, 1,
		colorsInfo[RED], 1, true, true, nullptr},
		
		{LIGHT, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 1.0 },
		{ 0.0, 0.0, 0.0 }, 0.1, 0.998, 10, 1,
		colorsInfo[WHITE], 1, true, true, nullptr},

		{DARK, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 1.0 },
		{ 0.0, 0.0, 0.0 }, 0.1, 0.998, 10, 1,
		colorsInfo[BLACK], 1, true, true, nullptr},
	};
}

using namespace part;

class Particle
{
public:
	Particle(bool v = true, Vector3 pos = { 0.0, 0.0, 0.0 }, Vector3 Vel = { 0.0, 0.0, 0.0 },
		Vector3 Acc = { 0.0, 0.0, 0.0 }, double m = 0.1, double damp = 0.998, double ls = 5, double size = 1,
		Vector4 c = { 0.19, 0.1, 0.2, 1.0 }, unsigned t = 0, int gen = 0);
	Particle(int type, bool v = true);
	Particle(Particle* p, bool v = true);
	Particle(ParticleInfo pI, bool v = true);
	~Particle();

	void integrate(double t);

protected:

	ParticleInfo pInfo;
	Vector3 force;
	double _inv_mass;
	double friction;

public:

	inline PxTransform& getPose() { return pInfo.pose; };
	inline Vector3& getVelocity() { return pInfo.velocity; };
	inline Vector3& getAcceleration() { return pInfo.acceleration; };
	inline double& getLifespan() { return pInfo.lifespan; };
	inline Vector4& getColor() { return pInfo.color; };
	inline double& getMass() { return pInfo.mass; };
	inline double& getSize() { return pInfo.size; };
	inline int& getType() { return pInfo._type; };
	inline RenderItem*& getRenderItem() { return pInfo.renderItem; }
	inline int& getGeneration() { return pInfo._generation; };
	inline double& getInvMass() { return _inv_mass; };
	inline void setPos(Vector3 pos) { pInfo.pose = PxTransform(pos.x, pos.y, pos.z); }

	inline void changeLifespan(double d) { pInfo.lifespan = d; _ls = d; }
	inline void setShape(_shape newShape) { 
		RenderItem* aux = pInfo.renderItem;
		switch (newShape)
		{
		case part::SPHERE:
			break;
		case part::CUBE:
			pInfo.renderItem = new RenderItem(CreateShape(PxBoxGeometry(pInfo.size, pInfo.size, pInfo.size)), &pInfo.pose, pInfo.color);
			break;
		default:
			break;
		}
		//delete aux;
	}

	double _ls;
	
	bool isAlive();

	enum ParticleType { DEFAULT, BULLET, FIREWORK};

	virtual Particle* clone() const;
	inline void die() { if (pInfo.renderItem != nullptr) pInfo.renderItem->release(); };
	inline void show() { if(pInfo.renderItem == nullptr) pInfo.renderItem = new RenderItem(CreateShape(PxSphereGeometry(pInfo.mass)), &pInfo.pose, pInfo.color); }
	inline int randomColor() { return rand() % nColors ; }

	void addForce(const Vector3& f) { force += f; }
	inline void clearForce() { force *= 0.0; }
};

