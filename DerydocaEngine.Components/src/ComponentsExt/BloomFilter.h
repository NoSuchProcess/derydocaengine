#pragma once
#include "Components\GameComponent.h"
#include "Rendering\RenderTexture.h"
#include "Components\Camera.h"

namespace DerydocaEngine::Ext
{

	class BloomFilter : public Components::GameComponent, Components::SelfRegister<BloomFilter>
	{
	public:
		GENINSTANCE(BloomFilter);

		BloomFilter();
		~BloomFilter();

		virtual void init();
		virtual void deserialize(const YAML::Node& compNode);
		virtual void update(const float deltaTime);

		float& getLumThresh() { return m_lumThresh; }
	private:
		float m_lumThresh;
		std::shared_ptr<Components::Camera> m_postProcessCamera;
		std::vector<float> m_weights;
		std::shared_ptr<Rendering::RenderTexture> m_blurTex;
		std::shared_ptr<Rendering::RenderTexture> m_blurTex2;

		float gauss(float const& x, float const& sigma2);
		void updateShader();
	};

}
