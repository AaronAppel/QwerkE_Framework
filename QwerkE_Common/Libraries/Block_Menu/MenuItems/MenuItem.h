#ifndef _MenuItem_H_
#define _MenuItem_H_

#include "../../../Math_Includes.h"
#include "../../Containers/MyLinkedList.h"

class Mesh;
class MenuWindow;
class ShaderProgram;

class MenuItem
{
public:
	MenuItem(vec2 resolution) { m_Resolution = resolution; };
	MenuItem(Mesh* mesh);
	~MenuItem();

	virtual void Update(vec2 mousePos);

	virtual void Draw();

	/* Functionality */
	virtual void LeftClick();
	virtual void RightClick(vec2 mousePos) {};
	virtual void MiddleClick(vec2 mousePos) {};
	virtual void Hover() {};

	/* Getters + Setters */
	// Getters
	Mesh* GetMesh() { return m_Mesh; };
	ShaderProgram* GetShader() { return m_Shader; };
	vec2 GetSize() { return m_Size; };
	vec2 GetPosition() { return m_Position; };

	// Setters
	void SetMesh(Mesh* mesh) { m_Mesh = mesh; };
	void SetShader(ShaderProgram* shader) { m_Shader = shader; };
	void SetParentWindow(MenuWindow* window);
	void SetPosition(vec2 position);
	void SetRotation(float rotation);
	void SetSize(vec2 size);
	void SetColor(vec4 color) { m_OriginalColor = color; };
	void SetResolution(vec2 resolution) { m_Resolution = resolution; };

	void UpdateTransform(); // re-calculate tranform mat4
	// getScreenPos
	// getScreenSize

protected:
	// Dialog
	void ShowDialogWindow() {};
	bool m_ShowDialog = false;
	// Dialog* m_Dialog = nullptr;

	MenuWindow* m_ParentWindow = nullptr;

	// Graphics
	Mesh* m_Mesh = nullptr;
	ShaderProgram* m_Shader = nullptr;

	vec4 m_OriginalColor = vec4(0.2f, 0.4f, 0.6f, 1.0f); // Used when no image
	vec4 m_Color = vec4(0.9f,0.9f,0.9f,1.0f); // Current colour

	vec2 m_Size = vec2(0.5f, 0.5f); // percentage of parent window size
	vec2 m_Position = vec2(0.5f, 0.5f); // percentage of parent window size for position
	vec2 m_Resolution = vec2(0, 0);
	float m_Rotation = 0.0f; // 2D rotation

	mat4 m_Transform;

	bool m_IsHighlighted = false;

	/* Overlay buttons */
	Linear2LinkedList<MenuItem*> m_OverLayButtons;
	void DrawOverlays();
};

#endif // !_MenuItem_H_