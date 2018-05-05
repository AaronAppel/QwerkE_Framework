#ifndef _RenderRoutine_H_
#define _RenderRoutine_H_

#include "Routine.h"
#include "../../../QwerkE_Common/Libraries/glew/GL/glew.h"

#include <vector>

class GameObject;
class RenderComponent;
class CameraComponent;

class RenderRoutine;
typedef void (RenderRoutine::*SetupUniformFunction)(CameraComponent* a_Camera); // Setup shader values function

class RenderRoutine : Routine
{
public:
	RenderRoutine() {};
	~RenderRoutine() {};

	void Initialize();

	void Draw(GameObject* a_Camera);

	void ResetUniformList() { SetDrawFunction(); };

private:
	/* Private variables */
	RenderComponent* m_pRender;
	std::vector<SetupUniformFunction> m_UniformSetupList;

	bool m_3D = true;

	////* Private functions *////
	void SetDrawFunction();

	/* Vertex uniform value assignment */
	void Setup3DTransform(CameraComponent* a_Camera);
	void Setup2DTransform(CameraComponent* a_Camera);

	/* Fragment uniform value assignment */
	void SetupColorUniforms(CameraComponent* a_Camera);
	void SetupTextureUniforms(CameraComponent* a_Camera);
	void SetupMaterialUniforms(CameraComponent* a_Camera);

	// Lighting
	void SetupLightingUniforms(CameraComponent* a_Camera);
	// Camera
	void SetupCameraUniforms(CameraComponent* a_Camera);
	/* Other */
	void SetupTextureUniforms(GLuint textures[], int size);
};

#endif //!_RenderRoutine_H_
