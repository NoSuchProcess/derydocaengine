#pragma once
#include "Components\GameComponent.h"
#include "Components\MeshRenderer.h"

namespace DerydocaEngine::Ext
{

	class WoodSliceTexture : public Components::GameComponent, Components::SelfRegister<WoodSliceTexture>
	{
	public:
		GENINSTANCE(WoodSliceTexture);
		WoodSliceTexture();
		~WoodSliceTexture();

		virtual void init();
		virtual void deserialize(const YAML::Node& compNode);
		virtual void preRender();

		std::shared_ptr<Components::Transform> getSliceMatrixTransform() { return m_sliceMatrixTransform; }
	private:
		std::shared_ptr<Components::Transform> m_sliceMatrixTransform;
		std::shared_ptr<Components::MeshRenderer> m_meshRenderer;
	};

}
