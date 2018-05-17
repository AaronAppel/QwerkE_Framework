#ifndef __MaterialData_H__
#define __MaterialData_H__

#include "../../../QwerkE_Common/Libraries/glew/GL/glew.h"

#include <string>

// TODO: Add functionality for new maps...
// Emissive
// Height
// Normals
// Shininess
// Opacity
// Displacement
// Lightmap
// Reflection

struct MaterialData
{
	std::string name = "Uninitialized";

	// Texture handles
	GLuint ambientHandle = 0;
	GLuint diffuseHandle = 0;
	GLuint specularHandle = 0;
	GLuint emissiveHandle = 0;
	GLuint heightHandle = 0;
	GLuint normalsHandle = 0;
	GLuint shininessHandle = 0;
	GLuint opacityHandle = 0;
	GLuint displacementHandle = 0;
	GLuint lightMapHandle = 0;
	GLuint reflectinoHandle = 0;

	// other data needed by shaders
	float shine = 0.5f;
	vec3 lightValue = vec3(1,1,1); // placeholder for more vec3s

	// texture names or ids
	std::string ambientName = "Uninitialized";
	std::string diffuseName = "Uninitialized";
	std::string specularName = "Uninitialized";
	std::string emissiveName = "Uninitialized";
	std::string heightName = "Uninitialized";
	std::string normalsName = "Uninitialized";
	std::string shininessName = "Uninitialized";
	std::string opacityName = "Uninitialized";
	std::string displacementName = "Uninitialized";
	std::string lightMapName = "Uninitialized";
	std::string reflectinoName = "Uninitialized";
	// std::string name = "Uninitialized"; // TODO: More map types

	// Constructors
	MaterialData() {};

	MaterialData(GLuint amb, GLuint diff, GLuint spec) : // simple
		ambientHandle(amb),
	diffuseHandle(diff),
	specularHandle(spec),
		shine(1.0f)
	{}

	MaterialData(std::string materialName, GLuint ambient, GLuint diffuse, GLuint specular, float shiny = 1.0f) : // simple + name
		name(materialName),
	ambientHandle(ambient),
	diffuseHandle(diffuse),
	specularHandle(specular),
	shine(shiny)
	{}

	// TODO: More constructors?
};

#endif //__MaterialData_H__
