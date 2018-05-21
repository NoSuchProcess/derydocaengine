#pragma once
#include "GameComponent.h"
#include <GL\glew.h>
#include "Material.h"
#include "BezierPatchMesh.h"

class TessellatedMeshRenderer : public GameComponent
{
public:
	GENINSTANCE(TessellatedMeshRenderer);

	TessellatedMeshRenderer();
	~TessellatedMeshRenderer();

	virtual void init();
	virtual void deserialize(YAML::Node compNode);
	void render(MatrixStack* matrixStack);
	Material* getMaterial() const { return m_material; }
private:
	BezierPatchMesh * m_mesh;
	GLuint m_vao;
	GLuint m_vbo;
	Material* m_material;
	int m_tessellationLevel = 4;
	Color m_lineColor;
};

