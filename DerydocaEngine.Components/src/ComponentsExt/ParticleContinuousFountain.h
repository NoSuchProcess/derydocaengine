#pragma once
#include "Components\GameComponent.h"
#include "Rendering\Material.h"

class YAML::Node;

namespace DerydocaEngine::Ext
{

	class ParticleContinuousFountain : public Components::GameComponent, Components::SelfRegister<ParticleContinuousFountain>
	{
	public:
		enum ParticleEmitterType
		{
			Point = 0,
			Cube = 1,
			Cone = 2
		};

		GENINSTANCE(ParticleContinuousFountain);

		ParticleContinuousFountain();
		~ParticleContinuousFountain();

		virtual void init();
		virtual void update(const float deltaTime);
		virtual void preRender();
		virtual void deserialize(const YAML::Node& compNode);
		virtual void render(const std::shared_ptr<Rendering::MatrixStack> matrixStack);

		glm::vec3& getVelocityMin() { return m_velocityMin; }
		glm::vec3& getVelocityMax() { return m_velocityMax; }
		int& getNumParticles() { return m_numParticles; }
		float& getLifetime() { return m_lifetime; }
		float& getAngle() { return m_angle; }
		glm::vec3 getAcceleration() { return m_acceleration; }
		glm::vec3 getEmitterSize() { return m_emitterSize; }
		float& getParticleSizeMin() { return m_particleSizeMin; }
		float& getParticleSizeMax() { return m_particleSizeMax; }

		void resetSimulation();

	private:
		int m_numParticles = 1000;
		std::shared_ptr<Rendering::Material> m_material;
		float m_time = 0.0f;
		float m_lifetime = 5.0f;
		glm::vec3 m_velocityMin = glm::vec3(1.25f);
		glm::vec3 m_velocityMax = glm::vec3(1.5f);
		float m_angle = 6.0f;
		float m_lastDeltaTime = 0.0f;
		glm::vec3 m_acceleration = glm::vec3(0.0f, -0.4f, 0.0f);
		unsigned int m_posBuf[2];
		unsigned int m_velBuf[2];
		unsigned int m_startTime[2];
		unsigned int m_initVel;
		unsigned int m_initPos;
		unsigned int m_particleArray[2];
		unsigned int m_feedback[2];
		unsigned int m_drawBuf = 1;
		unsigned int m_updateSub;
		unsigned int m_renderSub;
		std::shared_ptr<Components::Transform> m_trans;
		ParticleEmitterType m_emitterType;
		glm::vec3 m_emitterSize = glm::vec3(1.0, 1.0, 1.0);
		float m_particleSizeMin = 10.0f;
		float m_particleSizeMax = 10.0f;

		void initBuffers();
		float randFloat();
		void updateParticlePositions(float const& deltaTime);
		void renderParticles();
		glm::vec3 getVelocityFromCone();
		glm::vec3 getVelocityFromCube();
	};

}
