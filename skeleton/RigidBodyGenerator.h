#pragma once
#include "ParticleGenerator.h"
#include "RigidBody.h"

class RigidBodyGenerator : public ParticleGenerator
{
	Vector3 std_dev_pos, std_dev_vel;
	Vector3 iT;
	double std_dev_t;

	std::normal_distribution<float> _n{ minVar, maxVar };

	inline PxShape* generateShape(PxGeometryType::Enum s) {
		switch (s)
		{
		case physx::PxGeometryType::eSPHERE:
			return CreateShape(PxSphereGeometry(_model_particle.size));
			break;
			//case physx::PxGeometryType::ePLANE:
			//	break;
			//case physx::PxGeometryType::eCAPSULE:
			//	break;
		case physx::PxGeometryType::eBOX:
			CreateShape(PxBoxGeometry(_model_particle.size, _model_particle.size, _model_particle.size));
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
public:
	RigidBodyGenerator(PxMaterial* mat, Vector3 origin = { 0.0, 0.0, 0.0 }, Vector3 mean_velocity = { 0.0, 0.0, 0.0 }, Vector3 inertiaTensor = { -1,-1,-1 });
	RigidBodyGenerator(Particle* p, PxMaterial* mat, Vector3 origin = { 0.0, 0.0, 0.0 }, Vector3 mean_velocity = { 0.0, 0.0, 0.0 }, Vector3 inertiaTensor = { -1,-1,-1 });
	~RigidBodyGenerator() {};

	virtual void setVars();
	virtual Vector3 getRandomDist();

	virtual std::list<Particle*> generateParticles() {
		std::list<Particle*> ret;
		if (_u(_mt) <= _generation_prob) {
			for (int i = 0; i < _n_particles; ++i) {
				Vector3 pos = _origin + (getRandomDist() * offset);
				Particle* p = new RigidBody(pos, _model_particle.mass,
					generateShape(_model_particle.shape), _model_particle.color, { 0.5,0.5,0.5 }, iT);
				p->setVelocity(getRandomDist() * _mean_velocity);
				if (randomLifespan) {
					p->changeLifespan((_u(_mt) * randomLifespanLimits) + minLifespan);
				}

				ret.push_back(p);
			}
		}
		return ret;
	};
};

