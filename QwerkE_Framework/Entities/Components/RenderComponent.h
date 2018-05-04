#ifndef _RenderComponent_H_
#define _RenderComponent_H_

#include "../Components/Component.h"
#include "../../../Shared_Generic/Libraries/glew/GL/glew.h"
#include "../../../Shared_Generic/Math_Includes.h"
#include "../Components/Component.h"

#include <vector>

class Mesh;
class ShaderProgram;
class MaterialData;
class Model;

class RenderComponent : public Component
{
public:
	RenderComponent();
	~RenderComponent();

	/* Getters + Setters */
	// getters
	Mesh* GetMesh() { return m_pMesh; };
	ShaderProgram* GetShader() { return m_pShader; };
	GLuint GetCurrentTexture() { return m_CurrentTexture; };
	GLuint GetTextureList() { return m_CurrentTexture; };
	vec4 GetColour() { return m_Colour; };
	MaterialData* GetMaterial() { return m_Material; };
    Model* GetModel() { return m_Model; };

	// setters
	void SetMesh(Mesh* mesh);
	void SetShader(ShaderProgram* shader);
	void SetTexture(GLuint texture) { m_CurrentTexture = texture; };
	void SetColour(vec4 Colour) { m_Colour = Colour; };
	void SetMaterial(MaterialData* mat) { m_Material = mat; };
    void SetModel(Model* model) { m_Model = model; };

private:
	Mesh* m_pMesh = nullptr;
    Model* m_Model = nullptr;
	ShaderProgram* m_pShader = nullptr;
	// TODO:: Can m_Texture point to m_Material?
	// Is there an opportunity for efficiency?
	GLuint m_CurrentTexture = 0; // TODO: Allow for more than 1 texture for animation frames
	std::vector<GLuint> m_TextureList;
	vec4 m_Colour;
	MaterialData* m_Material = nullptr;
};

#endif //!_RenderComponent_H_
