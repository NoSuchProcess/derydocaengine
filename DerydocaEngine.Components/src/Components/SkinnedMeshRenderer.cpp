#include "EngineComponentsPch.h"
#include "SkinnedMeshRenderer.h"

#include "Components\Camera.h"
#include "Rendering\CameraManager.h"
#include "GameObject.h"
#include "Rendering\LightManager.h"
#include "Rendering\Material.h"
#include "Rendering\Mesh.h"
#include "Rendering\RenderTexture.h"
#include "Rendering\Shader.h"
#include "Rendering\ShaderLibrary.h"
#include "Resources\Serializers\SkeletonResourceSerializer.h"
#include "Rendering\Texture.h"
#include "Components\Transform.h"

namespace DerydocaEngine::Components
{

	SkinnedMeshRenderer::SkinnedMeshRenderer() :
		m_mesh(),
		m_material(),
		m_SkinnedMeshRendererCamera(),
		m_animation(),
		m_time(0.0f),
		m_boneMatrices()
	{
	}

	SkinnedMeshRenderer::~SkinnedMeshRenderer()
	{
	}

	void SkinnedMeshRenderer::deserialize(const YAML::Node& compNode)
	{
		auto material = getResourcePointer<Rendering::Material>(compNode, "Material");
		setMaterial(material);

		m_mesh = getResourcePointer<Rendering::Mesh>(compNode, "Mesh");

		m_animation = getResourcePointer<Animation::AnimationData>(compNode, "Animation");

		YAML::Node renderTextureSourceNode = compNode["RenderTextureSource"];
		if (renderTextureSourceNode && renderTextureSourceNode.IsScalar())
		{
			// Get the name that should be used to bind this texture to the shader
			std::string renderTextureName = "RenderTexture";
			YAML::Node renderTextureNameNode = compNode["RenderTextureName"];
			if (renderTextureNameNode != nullptr && renderTextureNameNode.IsScalar())
			{
				renderTextureName = renderTextureNameNode.as<std::string>();
			}

			boost::uuids::uuid renderTextureCameraId = renderTextureSourceNode.as<boost::uuids::uuid>();
			m_SkinnedMeshRendererCamera = ObjectLibrary::getInstance().getComponent<Camera>(renderTextureCameraId);
			material->setTexture(renderTextureName, m_SkinnedMeshRendererCamera->getRenderTexture());
		}
	}

	void SkinnedMeshRenderer::init()
	{
		m_boneMatrices.resize(m_mesh->getSkeleton()->getNumBones());
		m_animation->optimizeForSkeleton(m_mesh->getSkeleton());
	}

	void SkinnedMeshRenderer::render(std::shared_ptr<Rendering::MatrixStack> const matrixStack)
	{
		m_material->bind();
		m_material->getShader()->updateViaActiveCamera(matrixStack);
		m_animation->loadPose(m_time, m_boneMatrices, m_mesh->getSkeleton());
		m_material->setMat4Array("BoneMatrices", m_boneMatrices);

		Rendering::LightManager::getInstance().bindLightsToShader(matrixStack, getGameObject()->getTransform(), m_material->getShader());

		m_mesh->draw();

		m_material->unbind();
	}

	void SkinnedMeshRenderer::renderMesh(
		const std::shared_ptr<Rendering::MatrixStack> matrixStack,
		std::shared_ptr<Rendering::Material> material,
		const Rendering::Projection& projection,
		const std::shared_ptr<Transform> projectionTransform
	)
	{
		material->bind();
		material->getShader()->update(matrixStack, projection, projectionTransform);
		m_mesh->draw();
	}

}
