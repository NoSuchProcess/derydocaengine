#pragma once
#include "glm\glm.hpp"
#include "GameComponent.h"
#include "Color.h"
#include "MatrixStack.h"
#include "Material.h"
#include "Transform.h"
#include "Projection.h"

namespace DerydocaEngine::Components
{

	class Light : public GameComponent
	{
	public:
		GENINSTANCE(Light);

		/* Defines a light's type */
		enum LightType
		{
			/* A orthagonal light infinitely far away */
			Directional = 0,
			/* A light radiating in all directions */
			Point = 1,
			/* A light projected in a frustum */
			Spotlight = 2,
		};

		/* Defines how a light's shadowmap is filtered between texels */
		enum ShadowMapFilterType
		{
			/* Hard shadowing with visible aliasing */
			Nearest = 0,
			/* Linearly interpolate between texels for smooth shadow edges */
			Linear = 1
		};

		Light();
		~Light();

		void setLightType(LightType const& type) { m_lightType = type; }
		LightType getLightType() { return m_lightType; }

		glm::mat4 getProjectionMatrix();
		glm::mat4 getViewMatrix();

		void setColor(Color* const& color)
		{
			m_color.r = color->r;
			m_color.g = color->g;
			m_color.b = color->b;
			m_color.a = color->a;
		}
		Color getColor() { return m_color; }
		float getSpotlightExponent() { return m_spotlightExponent; }
		float getSpotlightCutoff() { return m_spotlightCutoff; }
		unsigned int getShadowMap() { return m_depthTexture; }
		bool isCastingShadows() { return m_castShadows; }
		bool setCastingShadows(bool const& castShadows) { m_castShadows = castShadows; }
		Rendering::Projection getProjection() { return m_projection; }
		glm::mat4 getShadowMatrix(glm::mat4 const& objectModelMatrix);
		float getShadowSoftness() const { return m_shadowSoftness; }

		void init();
		void deserialize(YAML::Node const& node);

		void renderShadowMap(GameObject* const& gameObject);
	private:
		void generateShadowMap();
		int getShadowMapFilterTypeEnum();

		LightType m_lightType = Point;
		Color m_color = Color(1, 1, 1, 1);
		float m_spotlightExponent;
		float m_spotlightCutoff;
		bool m_castShadows = false;
		int m_shadowMapHeight = 512;
		int m_shadowMapWidth = 512;
		unsigned int m_depthTexture;
		unsigned int m_shadowFBO;
		Rendering::MatrixStack m_matrixStack;
		Rendering::Material* m_shadowMapMaterial;
		Rendering::Projection m_projection;
		glm::mat4 m_shadowBias;
		ShadowMapFilterType m_shadowMapFilterType = ShadowMapFilterType::Nearest;
		float m_shadowSoftness = 0.01f;
	};

}
