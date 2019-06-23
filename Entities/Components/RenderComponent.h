#ifndef _RenderComponent_H_
#define _RenderComponent_H_

#include "Component.h"
#include "../../Graphics/Renderable.h"

#include <vector>
#include <string>

class ShaderProgram;
class Material;
class Mesh;

class RenderComponent : public Component
{
public:
	RenderComponent();
	RenderComponent(const char* objectRecipe);
	RenderComponent(const char* shaderName, const char* materialName, const char* meshName);
	~RenderComponent();

	void GenerateSchematic();

	void Setup(const char* shaderName, const char* materialName, const char* meshName);
	// void Clear();

	void AppendEmptyRenderables(int count);
	void AddRenderable(Renderable renderable);

	// Getters + Setters //
	// Getters
	std::string GetSchematicName() const { return m_SchematicName; }
	std::vector<Renderable>* GetRenderableList() { return &m_RenderableList; }
	const std::vector<Renderable>* SeeRenderableList() const { return &m_RenderableList; }

	// Setters
	void SetSchematicName(std::string name) { m_SchematicName = name; }
	void SetNameAtIndex(int index, std::string name);
	void SetShaderAtIndex(int index, ShaderProgram* shader);
	void SetMaterialAtIndex(int index, Material* material);
	void SetMeshAtIndex(int index, Mesh* mesh);

	const std::vector<Renderable>* LookAtRenderableList() { return &m_RenderableList; }

private:
	std::string m_SchematicName = "None";
	std::vector<Renderable> m_RenderableList;
};

#endif // !_RenderComponent_H_
