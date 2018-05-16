#include "MenuWindow.h"
#include "../../../QwerkE_Framework/Systems/Graphics/ShaderProgram/ShaderProgram.h"
#include "../../../QwerkE_Framework/Systems/Graphics/Mesh/Mesh.h"
#include "../MenuItems/ImageItem.h"

MenuWindow::MenuWindow(ShaderProgram* shader, Mesh* mesh, int items)
{
	m_Mesh = mesh;
	m_Mesh->SetupShaderAttributes(shader);

	for (int i = 0; i < items; i++) // Create and add items
	{
		MenuItem* tempItem = new ImageItem(m_Mesh);
		// MenuItem* tempItem = new AddButton(m_Mesh);
		((ImageItem*)tempItem)->SetTextureID(1); // TODO: Get texture handle
		((ImageItem*)tempItem)->SetShader(shader);

		tempItem->SetPosition(vec2(0.5f, 0.5f));
		tempItem->SetSize(vec2(0.25f, 0.25f));
		tempItem->SetRotation(0.0f);
		tempItem->SetColor(vec4(RandFloatInRange(0.0f, 1.0f), RandFloatInRange(0.0f, 1.0f), RandFloatInRange(0.0f, 1.0f), 1.0f));
		tempItem->SetParentWindow(this);

		m_Items.PushBack(tempItem);
	}
	m_Color = vec4(0.5, 0.5, 0.5, 1); // Background color
}

MenuWindow::~MenuWindow()
{
	for (int i = 0; i < m_Items.Size(); i++)
	{
		delete m_Items.At(i);
	}
	m_Items.Clear();
}

void MenuWindow::Setup()
{
	// Initialize values
	for (int i = 0; i < m_Items.Size(); i++)
	{
		m_Items.At(i)->SetParentWindow(this);
	}
}

void MenuWindow::Update(vec2 mousePos)
{
	// Update gizmos
	MovementGizmo(mousePos);
	ScalingGizmo(mousePos);

	// update items
	for (int i = 0; i < m_Items.Size(); i++)
	{
		MenuItem* tempItem = m_Items.At(i); // item's position is in window position % of dimensions(center +/- % of width/height)
		vec2 itemPosition = tempItem->GetPosition();
		vec2 itemSize = tempItem->GetSize();

		vec2 finalSize = itemSize * m_Size;

		float leftX = (m_Size.x * itemPosition.x) - (m_Size.x * itemSize.x * 0.5f) + (m_Position.x - m_Size.x * 0.5f);
		float bottomY = (m_Size.y * itemPosition.y) - (m_Size.y * itemSize.y * 0.5f) + (m_Position.y - m_Size.y * 0.5f);

		if (PointInBox(vec2(mousePos.x, mousePos.y), vec2(leftX + (m_Size.x * itemSize.x * 0.5f), bottomY + (m_Size.y * itemSize.y * 0.5f)), finalSize.x, finalSize.y))
		{
			m_Items.At(i)->Update(mousePos);
		}
		m_Items.At(i)->UpdateTransform();
	}
}

void MenuWindow::Draw()
{
	for (int i = 0; i < m_Items.Size(); i++)
	{
		m_Items.At(i)->Draw();
	}

	m_Shader->Use();
	m_Shader->SetUniformMat4("Transform", &m_Transform.m11);
	if (m_Texture != -1)
	{
		m_Shader->SetupTextures(&m_Texture, 1);
	}
	else
	{
		m_Shader->SetUniformFloat4("Color", m_Color.x, m_Color.y, m_Color.z, m_Color.w);
	}
	m_Mesh->Draw(); // Draw self
}

void MenuWindow::AddItem(MenuItem* item)
{
	m_Items.PushBack(item);
	item->SetParentWindow(this);
}

void MenuWindow::AddParentMenu(Menu* menu)
{
	m_ParentMenu = menu;
	UpdateTransform();
}

void MenuWindow::UpdateTransform()
{
	// mat4 temp;
	// temp = blue_rotate(temp, glm::radians(m_Angle), vec3(0, 0, 1));
	m_Transform.Rotate(m_Angle, 0, 0, 0);
	// temp = blue_translate(temp, vec3(m_Position.x / m_Resolution.x * 2 - 1, m_Position.y / m_Resolution.y * 2 - 1, 0));
	m_Transform.Translate(m_Position.x, m_Position.y, 0);
	vec3 t = vec3(m_Size.x * 2.0f / m_Resolution.x, m_Size.y * 2.0f / m_Resolution.y, 1);
	m_Transform.Scale(m_Size.x, m_Size.y, 1.0f);

	// temp = blue_scale(temp, t);
	// m_Transform = temp;
}

void MenuWindow::UpdateItems()
{
	ResizeItems();
	CenterItems();
}

void MenuWindow::ResizeItems()
{
	// size items to fit window and spacing values
	float horizontalSize = (m_Size.x - m_Spacing.x * (m_Columns + 1)) / m_Columns;
	float verticalSize = (m_Size.y - m_Spacing.y * (m_Rows + 1)) / m_Rows;

	// check too wide/tall
	bool widerThanTall = m_Size.x > m_Size.y;

	if (m_LockUniformSize) // use smaller value
	{
		if (widerThanTall) // wider
		{
			horizontalSize = verticalSize;
		}
		else // taller
		{
			verticalSize = horizontalSize;
		}
	}

	// check if out of bounds
	bool tooWide = m_Size.x < horizontalSize * m_Columns + m_Spacing.x * (m_Columns + 1);
	bool tooTall = m_Size.y < verticalSize * m_Rows + m_Spacing.y * (m_Rows + 1);

	if (tooWide)
	{
		float extra = (horizontalSize * m_Columns + m_Spacing.x * (m_Columns + 1)) - m_Size.x;
		horizontalSize *= m_Size.x / (m_Size.x + extra + m_Spacing.x);
		if (m_LockUniformSize)
		{
			verticalSize = horizontalSize;
		}
	}
	if (tooTall)
	{
		float extra = (verticalSize * m_Rows + m_Spacing.y * (m_Rows + 1)) - m_Size.y;
		verticalSize *= m_Size.y / (m_Size.y + extra + m_Spacing.y);
		if (m_LockUniformSize)
		{
			horizontalSize = verticalSize;
		}
	}
	// Update MenuItems size and transforms
	for (int i = 0; i < m_Items.Size(); i++)
	{
		m_Items.At(i)->SetSize(vec2(horizontalSize / m_Size.x, verticalSize / m_Size.y)); // percent
		m_Items.At(i)->UpdateTransform();
	}
}

void MenuWindow::CenterItems()
{
	vec2 t_ItemSize = m_Items.At(0)->GetSize(); // assume consistent size for all items
	vec2 t_Position = vec2(0, 0);

	float shiftValueX = 0.0f;
	float shiftValueY = 0.0f;
	if (m_VerticalAlignCenter) // center vertically
	{
		// calculate empty space y
		float emptySpace = m_Size.y - (m_Spacing.y * (m_Rows + 1)) - (m_Size.y * t_ItemSize.y * m_Rows);
		shiftValueY = emptySpace / m_Size.y * 0.5f;
	}

	if (m_HorizontalAlignCenter) // TODO::
	{
		// calculate empty space x
		float emptySpace = m_Size.x - (m_Spacing.x * (m_Columns + 1)) - (m_Size.x * t_ItemSize.x * m_Columns);
		shiftValueX = emptySpace / m_Size.x * 0.5f;
	}

	t_Position.y = m_Spacing.y + m_Size.y * t_ItemSize.y * 0.5f;

	int t_ItemIndex = 0;

	for (int i = 0; i < m_Rows; i++)
	{
		t_Position.x = m_Spacing.x + m_Size.x * t_ItemSize.x * 0.5f; // reset

		for (int j = 0; j < m_Columns; j++)
		{
			if (t_ItemIndex >= m_Items.Size())
				return; // safety check

			float t = 1 - t_Position.y / m_Size.y;

			// position as percent%
			m_Items.At(t_ItemIndex)->SetPosition(vec2((t_Position.x / m_Size.x) + shiftValueX, (1 - t_Position.y / m_Size.y) - shiftValueY));
			m_Items.At(t_ItemIndex)->UpdateTransform();

			t_ItemIndex++; // next item
			t_Position.x += m_Spacing.x + m_Size.x * t_ItemSize.x;
		}
		t_Position.y += m_Spacing.y + m_Size.y * t_ItemSize.y;
	}
}

void MenuWindow::LeftClick(vec2 mousePos)
{
	for (int i = 0; i < m_Items.Size(); i++)
	{
		MenuItem* tempItem = m_Items.At(i); // item's position is in window position % of dimensions(center +/- % of width/height)
		vec2 itemSize = tempItem->GetSize();
		vec2 itemPosition = tempItem->GetPosition();

		float LeftXBound = (m_Size.x * itemPosition.x) - (m_Size.x * itemSize.x * 0.5f) + (m_Position.x - m_Size.x * 0.5f); // 260
		float BottomYBound = (m_Size.y * itemPosition.y) - (m_Size.y * itemSize.y * 0.5f) + (m_Position.y - m_Size.y * 0.5f); // 350

		if (LeftXBound < mousePos.x &&
			mousePos.x < LeftXBound + (m_Size.x * itemSize.x))
			if (BottomYBound < mousePos.y && mousePos.y < BottomYBound + (m_Size.y * itemSize.y))
			{
				m_Items.At(i)->LeftClick();
			}
	}
}

void MenuWindow::SetResolution(vec2 resolution)
{
	for (int i = 0; i < m_Items.Size(); i++)
	{
		m_Items.At(i)->SetResolution(m_Resolution);
	}
	m_Resolution = resolution;
};

/* Private Functions */
void MenuWindow::MovementGizmo(vec2 mousePos)
{
	// Update position gizmo
	vec2 t_Position = vec2(m_Position.x, m_Position.y);
	vec2 t_Size = vec2(m_Size.x, m_Size.y);
	vec2 t_GizmoPos = t_Position - t_Size * 0.5f; // bottom left corner
	t_GizmoPos += (t_Size * m_PositionGizmo.position) - (m_PositionGizmo.size * 0.5f); // center of gizmo
	if (PointInBox(vec2(mousePos.x, mousePos.y), t_GizmoPos, m_PositionGizmo.size.x, m_PositionGizmo.size.y))
	{
		if (false) // debug_GetPlayerController()->IsButtonPressed(eGameButtons::Button_MouseRight))
		{
			vec2 t_ = vec2(-1, -1); // debug_GetPlayerController()->GetMousePosDelta();
			m_Position += vec2(t_.x, t_.y);
			UpdateTransform();
		}
	}
}

void MenuWindow::ScalingGizmo(vec2 mousePos)
{
	// Update scale gizmo
	vec2 t_Position = vec2(m_Position.x, m_Position.y);
	vec2 t_Size = vec2(m_Size.x, m_Size.y);
	vec2 t_GizmoPos = t_Position - t_Size * 0.5f; // bottom left corner
	t_GizmoPos += (t_Size * m_ScaleGizmo.position);
	t_GizmoPos -= vec2(m_ScaleGizmo.size.x * 0.5f, m_ScaleGizmo.size.y * -0.5f); // center of gizmo
	if (PointInBox(vec2(mousePos.x, mousePos.y), t_GizmoPos, m_ScaleGizmo.size.x, m_ScaleGizmo.size.y))
	{
		if (false) // debug_GetPlayerController()->IsButtonPressed(eGameButtons::Button_MouseRight))
		{
			vec2 t_ = vec2(-1, -1); // debug_GetPlayerController()->GetMousePosDelta();
			m_Size += vec2(t_.x * 2.0f, t_.y * -2.0f);
			UpdateTransform();
		}
	}
}