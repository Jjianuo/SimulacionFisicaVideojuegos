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
		PxGeometryType::Enum shape;
	};

	static ParticleInfo partType[nTypes] = {
		{DEFAULT, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 },
		{ 0.0, 0.0, 0.0 }, 1, 0.998, 5, 2,
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
		{ 0.0, 0.0, 0.0 }, 0.8, 0.998, 10, 1,
		colorsInfo[LIGHT_BLUE], 1, true, true, nullptr},

		{WATER, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 },
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
	inline ParticleInfo& getPInfo() { return pInfo; }

	inline PxTransform getPose() { return pInfo.pose; };
	virtual inline void setPos(Vector3 pos) { pInfo.pose = PxTransform(pos.x, pos.y, pos.z); }

	inline Vector3 getVelocity() { return pInfo.velocity; };
	virtual inline void setVelocity(Vector3 vel) { pInfo.velocity = vel; }

	inline Vector3 getAcceleration() { return pInfo.acceleration; };
	inline void setAcceleration(Vector3 acc) { pInfo.acceleration = acc; }

	inline double getLifespan() { return pInfo.lifespan; };
	inline void changeLifespan(double d) { pInfo.lifespan = d; _ls = d; }

	inline Vector4 getColor() { return pInfo.color; };
	inline void setColor(Vector4 c) { pInfo.color = c; pInfo.renderItem = new RenderItem(CreateShape(PxSphereGeometry(pInfo.size)), &pInfo.pose, pInfo.color);
	};

	inline double getMass() { return pInfo.mass; };
	inline void setMass(double m) { pInfo.mass = m; pInfo.renderItem = new RenderItem(CreateShape(PxSphereGeometry(pInfo.size)), &pInfo.pose, pInfo.color);
	};

	inline double getSize() { return pInfo.size; };
	inline void setSize(double s) { pInfo.size = s; pInfo.renderItem = new RenderItem(CreateShape(PxSphereGeometry(pInfo.size)), &pInfo.pose, pInfo.color);
	};

	inline int getType() { return pInfo._type; };

	inline RenderItem* getRenderItem() { return pInfo.renderItem; }
	inline void setRenderItem(PxShape* s, Vector3 t, Vector4 c) { 
		pInfo.shape = s->getGeometryType();
		pInfo.pose = PxTransform(t.x, t.y, t.z);
		pInfo.color = c;
		pInfo.renderItem = new RenderItem(s, &pInfo.pose, pInfo.color); 
	}

	inline int getGeneration() { return pInfo._generation; };
	inline void setGeneration(int g) { pInfo._generation = g; };

	inline double getInvMass() { return _inv_mass; };

	inline void setShape(PxGeometryType::Enum newShape) { 
		switch (newShape)
		{
		case PxGeometryType::eBOX:
			pInfo.renderItem = new RenderItem(CreateShape(PxBoxGeometry(pInfo.size, pInfo.size, pInfo.size)), &pInfo.pose, pInfo.color);
			break;
		default:
			break;
		}
		//delete aux;
	}

	inline PxShape* generateShape(PxGeometryType::Enum s) {
		switch (s)
		{
		case physx::PxGeometryType::eSPHERE:
			return CreateShape(PxSphereGeometry(pInfo.size));
			break;
		//case physx::PxGeometryType::ePLANE:
		//	break;
		//case physx::PxGeometryType::eCAPSULE:
		//	break;
		case physx::PxGeometryType::eBOX:
			CreateShape(PxBoxGeometry(pInfo.size, pInfo.size, pInfo.size));
			break;
		//case physx::PxGeometryType::eCONVEXMESH:
		//	break;
		//case physx::PxGeometryType::eTRIANGLEMESH:
		//	break;
		//case physx::PxGeometryType::eHEIGHTFIELD:
		//	break;
		//case physx::PxGeometryType::eGEOMETRY_COUNT:
		//	break;
		//case physx::PxGeometryType::eINVALID:
		//	break;
		default:
			break;
		}
	}

	double _ls;
	
	bool isAlive();

	enum ParticleType { DEFAULT, BULLET, FIREWORK};

	virtual Particle* clone() const;
	inline virtual void die() { if (pInfo.renderItem != nullptr) pInfo.renderItem->release(); };
	inline void show() { if(pInfo.renderItem == nullptr) pInfo.renderItem = new RenderItem(CreateShape(PxSphereGeometry(pInfo.mass)), &pInfo.pose, pInfo.color); }
	inline int randomColor() { return rand() % nColors ; }

	virtual void addForce(const Vector3& f) { force += f; }
	virtual inline void clearForce() { force *= 0.0; }
};

