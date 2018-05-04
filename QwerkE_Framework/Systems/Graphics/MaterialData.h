#ifndef __MaterialData_H__
#define __MaterialData_H__

class MaterialData
{
public:
	std::string name = "";

	// Texture handles
	GLuint ambientHandle = 0;
	GLuint diffuseHandle = 0;
	GLuint specularHandle = 0;
	float shine = 1.0f;

	// Constructors
	MaterialData() {};

	MaterialData(GLuint amb, GLuint diff, GLuint spec) :
		ambientHandle(amb),
	diffuseHandle(diff),
	specularHandle(spec),
		shine(1.0f)
	{}

	MaterialData(std::string materialName, GLuint ambient, GLuint diffuse, GLuint specular, float shiny = 1.0f) :
		name(materialName),
	ambientHandle(ambient),
	diffuseHandle(diffuse),
	specularHandle(specular),
	shine(shiny)
	{}


};

#endif //__MaterialData_H__
