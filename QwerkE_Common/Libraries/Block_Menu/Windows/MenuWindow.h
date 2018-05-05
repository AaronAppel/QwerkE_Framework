#ifndef _MenuWindow_H_
#define _MenuWindow_H_

#include "../../../Math_Includes.h"
#include "../../Custom_Classes/MyLinkedList.h"
#include "../glew/GL/glew.h"

struct Block_Menu_Gizmo
{
	Block_Menu_Gizmo(vec2 pos, vec2 widthHeight)
	{
		position = pos;
		size = widthHeight;
	}
	vec2 position = vec2(0.0f, 0.0f);
	vec2 size = vec2(1.0f, 1.0f); // change to vec2 scale(), vec2 size(), other
};

class MenuItem;
class Mesh;
class Menu;
class ShaderProgram;

class MenuWindow
{
public:
	MenuWindow(vec2 resolution) { m_Resolution = resolution; };
	MenuWindow(ShaderProgram* shader, Mesh* mesh, int items = 0);
	~MenuWindow();

	// virtual void Init() = 0; // Creates abstract class
	void Setup();

	void Update(vec2 mousePos);
	void UpdateTransform();
	void UpdateItems();

	void Draw();

	// Items
	void CreateItem() {}; // TODO::
	void AddItem(MenuItem* item);
	void AddParentMenu(Menu* menu);

	void RemoveItem() {};

	// Interaction
	void LeftClick(vec2 mousePos);
	void RightClick(vec2 mousePos) {};
	void MiddleClick(vec2 mousePos) {};

	/* Getters + Setters */
	// Getters
	vec2 GetPosition() { return m_Position; };
	vec2 GetSize() { return m_Size; };
	Mesh* GetMesh() { return m_Mesh; }
	ShaderProgram* GetShader() { return m_Shader; }
	GLuint GetTexture() { return m_Texture; }
	bool GetIsInteracting() { return m_IsInteracting; }

	// Setters
	void SetPosition(vec2 position) { m_Position = position; };
	void SetSize(vec2 size) { m_Size = size; };
	void SetDimensions(int columns, int rows) { m_Columns = columns; m_Rows = rows; };
	void SetResolution(vec2 resolution);
	void SetSpacing(vec2 spacing) { m_Spacing = spacing; };
	//void SetItemScale(glm::vec2 scale) { m_ItemScale = scale; };
	void SetMesh(Mesh* mesh) { m_Mesh = mesh; }
	void SetShader(ShaderProgram* shader) { m_Shader = shader; }
	void SetTexture(GLuint texture) { m_Texture = texture; }
	void SetUniformSizing(bool locked) { m_LockUniformSize = locked; ResizeItems(); };

protected:
	int m_Rows = 1;
	int m_Columns = 1;

	vec2 m_Spacing = vec2(10.0f, 10.0f); // non-Uniform spacing?

	bool m_LockUniformSize = false;
	bool m_VerticalAlignCenter = true; // false = top align
	bool m_HorizontalAlignCenter = true; // false = left align

	int m_Type = 0; // grid

	Menu* m_ParentMenu = nullptr;
	Linear2LinkedList<MenuItem*> m_Items;

	Mesh* m_Mesh = nullptr;
	ShaderProgram* m_Shader = nullptr;
	GLuint m_Texture = -1;

	mat4 m_Transform;
	vec4 m_Color = vec4(1, 1, 1, 1);

	vec2 m_Position = vec2(1, 1);
	vec2 m_Size = vec2(1, 1);
	vec2 m_Resolution = vec2(0,0);
	float m_Angle = 0.0f;

	Block_Menu_Gizmo m_PositionGizmo = Block_Menu_Gizmo(vec2(1, 1), vec2(100, 100)); // pos as % of window size from bottom left, pixel width and height
	Block_Menu_Gizmo m_ScaleGizmo = Block_Menu_Gizmo(vec2(1, 0), vec2(100, 100)); // pos as % of window size from bottom left, pixel width and height

	/* Private Functions */
	// Menu Items
	void ResizeItems();
	void CenterItems();
	// Gizmos
	void MovementGizmo(vec2 mousePos);
	void ScalingGizmo(vec2 mousePos);
	bool m_IsInteracting = false; // TODO: Determine when mouse is interacting with Gizmos
};

#endif // !_MenuWindow_H_