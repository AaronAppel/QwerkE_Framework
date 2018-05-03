#ifndef __ImageItem_H_
#define __ImageItem_H_

#include "MenuItem.h"
#include "../glew/GL/glew.h"

class Mesh;
class ShaderProgram;

class ImageItem : public MenuItem
{
public:
	ImageItem(Mesh* mesh);
	~ImageItem();

	void Draw();
	virtual void LeftClick();

	/* Setter + Getters */
	void SetTextureID(GLuint texture) { m_TextureID = texture; };
	void SetShader(ShaderProgram* shader) { m_Shader = shader; };

private:
	ShaderProgram* m_Shader = nullptr;
	GLuint m_TextureID = 0;
};


#endif // __ImageItem_H_