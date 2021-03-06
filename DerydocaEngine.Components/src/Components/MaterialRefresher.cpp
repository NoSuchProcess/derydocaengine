#include "EngineComponentsPch.h"
#include "MaterialRefresher.h"

#include <boost/filesystem.hpp>
#include "Rendering\Material.h"
#include "Components\MeshRenderer.h"
#include "Rendering\Shader.h"
#include "ComponentsExt\TessellatedMeshRenderer.h"
#include "SkinnedMeshRenderer.h"

namespace DerydocaEngine::Components
{

	MaterialRefresher::MaterialRefresher() :
		m_rendererType(0),
		m_meshRenderer(),
		m_skinnedMeshRenderer(),
		m_tessMeshRenderer(),
		m_vertexShaderExists(false),
		m_fragmentShaderExists(false),
		m_geometryShaderExists(false),
		m_tessEvalShaderExists(false),
		m_shaderLoadPath(),
		m_vertexShaderPath(),
		m_fragmentShaderPath(),
		m_geometryShaderPath(),
		m_tessEvalShaderPath(),
		m_tessControlShaderPath(),
		m_vertexShaderModifiedTime(),
		m_fragmentShaderModifiedTime(),
		m_geometryShaderModifiedTime(),
		m_tessEvalShaderModifiedTime(),
		m_tessControlShaderModifiedTime()
	{
	}

	MaterialRefresher::~MaterialRefresher()
	{
	}

	bool getLastModifiedTime(std::string const& filePath, std::time_t &time)
	{
		if (!boost::filesystem::exists(filePath))
		{
			return false;
		}

		time = boost::filesystem::last_write_time(filePath);
		return true;
	}

	void MaterialRefresher::init()
	{
		m_meshRenderer = getComponent<MeshRenderer>();
		std::shared_ptr<Rendering::Material> material;
		if (m_meshRenderer != nullptr)
		{
			m_rendererType = 0;
			material = m_meshRenderer->getMaterial();
		}
		else
		{
			m_skinnedMeshRenderer = getComponent<SkinnedMeshRenderer>();
			if (m_skinnedMeshRenderer != nullptr)
			{
				m_rendererType = 1;
				material = m_skinnedMeshRenderer->getMaterial();
			}
			else
			{
				m_rendererType = 2;
				m_tessMeshRenderer = getComponent<Ext::TessellatedMeshRenderer>();
				material = m_tessMeshRenderer->getMaterial();
			}
		}
		assert(material);

		auto shader = material->getShader();
		assert(shader);

		m_shaderLoadPath = shader->GetLoadPath();
		m_vertexShaderPath = shader->GetVertexShaderPath();
		m_fragmentShaderPath = shader->GetFragmentShaderPath();
		m_geometryShaderPath = shader->GetGeometryShaderPath();
		m_tessEvalShaderPath = shader->GetTessellationEvaluationShaderPath();
		m_tessControlShaderPath = shader->GetTesslleationControlShaderPath();

		// Store the initial modified time
		m_vertexShaderExists = getLastModifiedTime(m_vertexShaderPath.c_str(), m_vertexShaderModifiedTime);
		m_fragmentShaderExists = getLastModifiedTime(m_fragmentShaderPath.c_str(), m_fragmentShaderModifiedTime);
		m_geometryShaderExists = getLastModifiedTime(m_geometryShaderPath.c_str(), m_geometryShaderModifiedTime);
		m_tessEvalShaderExists = getLastModifiedTime(m_tessEvalShaderPath.c_str(), m_tessEvalShaderModifiedTime);
		m_tessControlShaderExists = getLastModifiedTime(m_tessControlShaderPath.c_str(), m_tessControlShaderModifiedTime);
	}

	void MaterialRefresher::update(const float deltaTime)
	{
		if (isShaderSourceUpdated()) {
			refreshMaterial();
		}
	}

	void MaterialRefresher::refreshMaterial()
	{
		// Remember the last modified time for later
		m_vertexShaderExists = getLastModifiedTime(m_vertexShaderPath.c_str(), m_vertexShaderModifiedTime);
		m_fragmentShaderExists = getLastModifiedTime(m_fragmentShaderPath.c_str(), m_fragmentShaderModifiedTime);
		m_geometryShaderExists = getLastModifiedTime(m_geometryShaderPath.c_str(), m_geometryShaderModifiedTime);
		m_tessEvalShaderExists = getLastModifiedTime(m_tessEvalShaderPath.c_str(), m_tessEvalShaderModifiedTime);
		m_tessControlShaderExists = getLastModifiedTime(m_tessControlShaderPath.c_str(), m_tessControlShaderModifiedTime);

		printf("Unloading the previous material.\n");
		std::shared_ptr<Rendering::Material> mat = nullptr;
		switch (m_rendererType)
		{
		case 0:
			mat = m_meshRenderer->getMaterial();
			break;
		case 1:
			mat = m_skinnedMeshRenderer->getMaterial();
			break;
		case 2:
			mat = m_tessMeshRenderer->getMaterial();
			break;
		default:
			break;
		}
		auto oldShader = mat->getShader();

		printf("Reloading new material.\n");
		auto newShader = std::make_shared<Rendering::Shader>(m_shaderLoadPath);
		mat->setShader(newShader);
		printf("Material reload finished.\n");
	}

	bool MaterialRefresher::isShaderSourceUpdated()
	{
		time_t tempFileTime;

		// Check the vertex shader
		if (
			m_vertexShaderExists &&
			getLastModifiedTime(m_vertexShaderPath.c_str(), tempFileTime) &&
			difftime(tempFileTime, m_vertexShaderModifiedTime) != 0) {
			return true;
		}

		// Check the fragment shader
		if (
			m_fragmentShaderExists &&
			getLastModifiedTime(m_fragmentShaderPath.c_str(), tempFileTime) &&
			difftime(tempFileTime, m_fragmentShaderModifiedTime) != 0) {
			return true;
		}

		// Check the geometry shader
		if (
			m_geometryShaderExists &&
			getLastModifiedTime(m_geometryShaderPath.c_str(), tempFileTime) &&
			difftime(tempFileTime, m_geometryShaderModifiedTime) != 0) {
			return true;
		}

		// Check the tesselation evaluation shader
		if (
			m_tessEvalShaderExists &&
			getLastModifiedTime(m_tessEvalShaderPath.c_str(), tempFileTime) &&
			difftime(tempFileTime, m_tessEvalShaderModifiedTime) != 0) {
			return true;
		}

		// Check the tesselation control shader
		if (
			m_tessControlShaderExists &&
			getLastModifiedTime(m_tessControlShaderPath.c_str(), tempFileTime) &&
			difftime(tempFileTime, m_tessControlShaderModifiedTime) != 0) {
			return true;
		}

		// If neither were changed, return false
		return false;
	}

}
