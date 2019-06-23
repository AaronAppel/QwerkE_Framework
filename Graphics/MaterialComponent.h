#ifndef _MaterialComponent_H_
#define _MaterialComponent_H_

#include "../../QwerkE_Common/Libraries/glew/GL/glew.h"
#include "../Headers/QwerkE_Enums.h"

#include <string>

struct MaterialComponent
{
	eMaterialMaps s_Type = eMaterialMaps::MatMap_Null;

	std::string s_TextureName = gc_DefaultStringValue;

	GLuint s_Handle = 0;

	// constructors/destructors
	MaterialComponent();
	MaterialComponent(std::string name, GLuint handle) :
		s_TextureName(name),
		s_Handle(handle){}
	~MaterialComponent();
};

#endif // !_MaterialComponent_H_
