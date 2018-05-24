#ifndef _RenderComponent_H_
#define _RenderComponent_H_

#include "Component.h"
#include "../../Graphics/Renderable.h"

#include <vector>

class ShaderProgram;
class MaterialData;
class Mesh;

class RenderComponent : public Component
{
public:
	RenderComponent();
	RenderComponent(const char* objectRecipe) {}
	RenderComponent(const char* shaderName, const char* materialName, const char* meshName);
	~RenderComponent();

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

#endif // !_RenderComponent_H_
