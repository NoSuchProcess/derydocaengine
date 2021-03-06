#pragma once
#include "Components\GameComponent.h"
#include "Rendering\MatrixStack.h"
#include "Rendering\Mesh.h"

namespace DerydocaEngine {
	namespace Components {
		class MeshRenderer;
	}
	namespace Rendering {
		class Texture;
	}
}

namespace DerydocaEngine::Components
{

	class Terrain : public GameComponent, SelfRegister<Terrain>
	{
	public:
		GENINSTANCE(Terrain);
		Terrain();
		Terrain(const std::string& fileName, float const& unitScale, float const& heightScale);
		Terrain(int const& width, int const& depth, float const& unitScale, float const& heightScale);
		~Terrain();

		void draw();
		void updateMesh();

		void setTextureSlot(int const& slot, std::shared_ptr<Rendering::Texture> texture);
		void init();

		virtual void render(const std::shared_ptr<Rendering::MatrixStack> matrixStack);
		void deserialize(const YAML::Node& node);
	private:
		int m_width;
		int m_depth;
		float m_unitScale;
		float m_heightScale;
		float** m_heightData;
		std::shared_ptr<Rendering::Mesh> m_mesh;
		std::shared_ptr<MeshRenderer> m_meshRenderer;

		void loadTerrainFromTexture(const std::string & fileName, float const& unitScale, float const& heightScale);
	};

}
