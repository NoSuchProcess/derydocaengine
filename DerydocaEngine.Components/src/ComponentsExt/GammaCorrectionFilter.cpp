#include "EngineComponentsPch.h"
#include "GammaCorrectionFilter.h"
#include "Rendering\Shader.h"
#include <iostream>
#include "Rendering\Material.h"

namespace DerydocaEngine::Ext
{

	void GammaCorrectionFilter::init()
	{
		m_postProcessCamera = getComponent<Components::Camera>();
		if (m_postProcessCamera == nullptr)
		{
			std::cout << "No camera was found attached to this EdgeDetectionFilter component. A camera with a render texture is required to use this component.\n";
			return;
		}
	}

	void GammaCorrectionFilter::deserialize(YAML::Node const& compNode)
	{
		YAML::Node lumThreshNode = compNode["lumThresh"];
		if (lumThreshNode)
		{
			m_gamma = compNode["gamma"].as<float>();
		}
	}

	void GammaCorrectionFilter::update(float const& deltaTime)
	{
		updateShader();
	}

	void GammaCorrectionFilter::updateShader()
	{
		auto shader = m_postProcessCamera->getPostProcessShader();
		if (shader == nullptr)
		{
			return;
		}

		shader->setFloat("Gamma", m_gamma);
	}

}