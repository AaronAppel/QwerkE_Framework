#include "../../../QwerkE_Common/Libraries/Block_Menu/Block_Menu.h"
#include "Factory.h"
#include "../../../QwerkE_Common/Math_Includes.h"
#include "../Graphics/Mesh/Mesh.h"
#include "../../Systems/ResourceManager/ResourceManager.h"

// Internal Creation Functions
Menu* Factory::CreateMenu()
{
	return new Menu(vec2(0,0));
}
MenuWindow* Factory::CreateMenuWindow()
{
	return new MenuWindow(vec2(0, 0));
}
MenuItem* Factory::CreateMenuItem()
{
	return new MenuItem(vec2(0, 0));
}
/* Block_Menu */
// Menus
Menu* Factory::CreatePresetMenu1()
{
	Menu* menu = CreateMenu();
	int width = 3, height = 4;
	MenuWindow* t_Window = CreateBasicGridMenuWindow(vec2(width, height), width * height);
	menu->AddWindow(t_Window);
	t_Window->AddParentMenu(menu); // Link
	t_Window->UpdateItems();

	return menu;
}
Menu* Factory::CreatePresetMenu2()
{
	Menu* menu = CreateMenu();
	int width = 3, height = 4;
	MenuWindow* t_Window = CreateImageGridMenuWindow(vec2(width, height), width * height);
	menu->AddWindow(t_Window);
	t_Window->AddParentMenu(menu); // Link
	t_Window->UpdateItems();

	return menu;
}
// MenuWindows
MenuWindow* Factory::CreateBasicGridMenuWindow(vec2 size, int numItems)
{
	MenuWindow* menuWindow = CreateMenuWindow();

	menuWindow->SetShader(m_pResources->GetShader("2DMenuText"));
	// menuWindow->SetShader(m_pResources->GetShader("2DMenu"));
	menuWindow->SetMesh(m_pResources->GetMesh("Box"));
	menuWindow->GetMesh()->SetupShaderAttributes(menuWindow->GetShader());
	menuWindow->SetTexture(m_pResources->GetTexture("Menu_Border1.png"));

	menuWindow->SetSpacing(vec2(8, 15));
	menuWindow->SetResolution(vec2(g_WindowWidth, g_WindowHeight)); // TODO: Handle resolution
	menuWindow->SetDimensions((int)size.x, (int)size.y);
	menuWindow->SetPosition(vec2(115.0f, g_WindowHeight / 1.6f)); // Centered
	menuWindow->SetSize(vec2(200, 450)); // pixels
	menuWindow->SetUniformSizing(false);

	// Add items
	for (int i = 0; i < numItems; i++)
	{
		menuWindow->AddItem(CreateBasicMenuItem());
	}

	menuWindow->Setup();

	return menuWindow;
}
MenuWindow* Factory::CreateImageGridMenuWindow(vec2 size, int numItems)
{
	MenuWindow* menuWindow = CreateMenuWindow();

	menuWindow->SetShader(m_pResources->GetShader("2DMenuText"));
	// menuWindow->SetShader(m_pResources->GetShader("2DMenu"));
	menuWindow->SetMesh(m_pResources->GetMesh("Box"));
	menuWindow->GetMesh()->SetupShaderAttributes(menuWindow->GetShader());
	menuWindow->SetTexture(m_pResources->GetTexture("Menu_Border1.png"));

	menuWindow->SetSpacing(vec2(8, 15));
	menuWindow->SetResolution(vec2(g_WindowWidth, g_WindowHeight)); // TODO: Handle resolution
	menuWindow->SetDimensions((int)size.x, (int)size.y);
	menuWindow->SetPosition(vec2(115.0f, g_WindowHeight / 1.6f)); // Centered
	menuWindow->SetSize(vec2(200, 450)); // pixels
	menuWindow->SetUniformSizing(false);

	// Add items
	for (int i = 0; i < numItems; i++)
	{
		menuWindow->AddItem(CreateImageMenuItem());
	}

	menuWindow->Setup();

	return menuWindow;
}
// MenuItems
MenuItem* Factory::CreateBasicMenuItem()
{
	// MenuItem* menuItem = new ImageItem(m_pResources->GetMesh("Box"));
	MenuItem* menuItem = new MenuItem(m_pResources->GetMesh("Box"));

	// ((ImageItem*)menuItem)->SetTextureID(m_pResources->GetTexture("FlashHeal")); // TODO: Get texture handle
	// ((ImageItem*)menuItem)->SetShader(m_pResources->GetShader("2DMenuText"));

	menuItem->SetShader(m_pResources->GetShader("2DMenu"));

	menuItem->GetMesh()->SetupShaderAttributes(menuItem->GetShader());

	menuItem->SetPosition(vec2(0.5f, 0.5f));
	menuItem->SetSize(vec2(0.5f, 0.5f));
	menuItem->SetRotation(0.0f);
	menuItem->SetColor(vec4(RandFloatInRange(0.0f, 1.0f), RandFloatInRange(0.0f, 1.0f), RandFloatInRange(0.0f, 1.0f), 1.0f));

	return menuItem;
}
MenuItem* Factory::CreateImageMenuItem()
{
	// MenuItem* menuItem = new ImageItem(m_pResources->GetMesh("Box"));
	ImageItem* menuItem = new ImageItem(m_pResources->GetMesh("Box"));

	// ((ImageItem*)menuItem)->SetTextureID(m_pResources->GetTexture("FlashHeal")); // TODO: Get texture handle
	// ((ImageItem*)menuItem)->SetShader(m_pResources->GetShader("2DMenuText"));

	menuItem->SetShader(m_pResources->GetShader("2DMenuText"));
	menuItem->SetTextureID(m_pResources->GetTexture("container.png"));
	menuItem->GetMesh()->SetupShaderAttributes(menuItem->GetShader());

	menuItem->SetPosition(vec2(0.5f, 0.5f));
	menuItem->SetSize(vec2(0.5f, 0.5f));
	menuItem->SetRotation(0.0f);
	menuItem->SetColor(vec4(RandFloatInRange(0.0f, 1.0f), RandFloatInRange(0.0f, 1.0f), RandFloatInRange(0.0f, 1.0f), 1.0f));

	return menuItem;
}