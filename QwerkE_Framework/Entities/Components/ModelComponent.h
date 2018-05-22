#ifndef _ModelComponent_H_
#define _ModelComponent_H_

#include "Component.h"
#include "../../Systems/Graphics/Gfx_Classes/Renderable.h"

#include <vector>

class ShaderProgram;
class MaterialData;
class Mesh;

class ModelComponent : public Component
{
public:
	ModelComponent();
	ModelComponent(const char* objectRecipe) {}
	ModelComponent(const char* shaderName, const char* materialName, const char* meshName);
	~ModelComponent();

	// TODO:
	void GenerateRecipe();

	void Setup(const char* shaderName, const char* materialName, const char* meshName);
	// void Clear();

	void AppendEmptyRenderables(int count);
	void AddRenderable(Renderable renderable);

	void SetShaderAtIndex(int index, ShaderProgram* shader);
	void SetMaterialAtIndex(int index, MaterialData* material);
	void SetMeshAtIndex(int index, Mesh* mesh);

	const std::vector<Renderable>* LookAtRenderableList() { return &m_RenderableList; }

private:
	std::vector<Renderable> m_RenderableList;
};

#endif // !_ModelComponent_H_
