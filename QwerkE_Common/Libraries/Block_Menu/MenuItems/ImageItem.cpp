#include "ImageItem.h"
#include "../../../Shared_Engine/Systems/Graphics/ShaderProgram/ShaderProgram.h"
#include "../../../Shared_Engine/Systems/Graphics/Model/Mesh/Mesh.h"

ImageItem::ImageItem(Mesh* mesh) : MenuItem(mesh)
{
}

ImageItem::~ImageItem()
{
}

void ImageItem::Draw()
{
	m_Shader->Use();
	m_Shader->SetUniformMat4("Transform", &m_Transform.m11);
	m_Shader->SetupTextures(&m_TextureID, 1);
	m_Mesh->Draw();
}

void ImageItem::LeftClick()
{
	// do something
}