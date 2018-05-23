#ifndef _RenderRoutine_H_
#define _RenderRoutine_H_

#include "Routine.h"
#include "../../../QwerkE_Common/Libraries/glew/GL/glew.h"
#include "../../Systems/Graphics/Gfx_Classes/Renderable.h"

#include <vector>

class GameObject;
class CameraComponent;
class ShaderProgramData;
class Mesh;
class RenderComponent;
class MaterialData;
class RenderRoutine;

typedef void (RenderRoutine::*DrawFunc)(GameObject* a_Camera); // draw mesh or model
// TODO: Look at improving arguments
typedef void (RenderRoutine::*SetupUniformFunction)(CameraComponent* a_Camera, Renderable* renderable); // Setup shader values function

class RenderRoutine : Routine
{
public:
	RenderRoutine() {};
	~RenderRoutine() {};

	void Initialize();

	void Draw(GameObject* a_Camera) { (this->*m_DrawFunc)(a_Camera); };

	void ResetUniformList() { SetDrawFunctions(); }; // TODO: External use?

private:
	/* Private variables */
	DrawFunc m_DrawFunc = &RenderRoutine::NullDraw;
	RenderComponent* m_pRenderComp = nullptr;
	std::vector<std::vector<SetupUniformFunction>> m_UniformSetupList;

	bool m_3D = true; // 2D/3D optimization TODO: Remove?

	////* Private functions *////
	void DrawMeshData(GameObject* a_Camera);
	void NullDraw(GameObject* a_Camera); // not setup

	//// Uniform value assignment ////
	void SetDrawFunctions();

	/* Vertex uniform value assignment */
	void Setup3DTransform(CameraComponent* a_Camera, Renderable* renderable);
	void Setup2DTransform(CameraComponent* a_Camera, Renderable* renderable);

	/* Fragment uniform value assignment */
	void SetupColorUniforms(CameraComponent* a_Camera, Renderable* renderable);
	void SetupMaterialUniforms(CameraComponent* a_Camera, Renderable* renderable);

	// Lighting
	void SetupLightingUniforms(CameraComponent* a_Camera, Renderable* renderable);
	// Camera
	void SetupCameraUniforms(CameraComponent* a_Camera, Renderable* renderable);
	/* Other */
	void SetupTextureUniforms(GLuint textures[], int size, ShaderProgramData* shader);
};

#endif //!_RenderRoutine_H_
