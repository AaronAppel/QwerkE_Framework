#ifndef __MaterialData_H__
#define __MaterialData_H__

#include "../../../QwerkE_Common/Libraries/glew/GL/glew.h"

#include <string>

struct MaterialData
{
	std::string s_Name = "Uninitialized";

	// Texture handles
	GLuint s_AmbientHandle = 0;
	GLuint s_DiffuseHandle = 0;
	GLuint s_SpecularHandle = 0;
	GLuint s_EmissiveHandle = 0;
	GLuint s_HeightHandle = 0;
	GLuint s_NormalsHandle = 0;
	GLuint s_ShininessHandle = 0;
	GLuint s_OpacityHandle = 0;
	GLuint s_DisplacementHandle = 0;
	GLuint s_LightMapHandle = 0;
	GLuint s_ReflectionHandle = 0;

	// other data needed by shaders
	float s_Shine = 0.5f;
	vec4 s_LightValue = vec4(1,1,1,1); // placeholder for more vec3/4s

	// texture names or ids
	std::string s_AmbientName = "Uninitialized";
	std::string s_DiffuseName = "Uninitialized";
	std::string s_SpecularName = "Uninitialized";
	std::string s_EmissiveName = "Uninitialized";
	std::string s_HeightName = "Uninitialized";
	std::string s_NormalsName = "Uninitialized";
	std::string s_ShininessName = "Uninitialized";
	std::string s_OpacityName = "Uninitialized";
	std::string s_DisplacementName = "Uninitialized";
	std::string s_LightMapName = "Uninitialized";
	std::string s_ReflectionName = "Uninitialized";

	// Constructors
	MaterialData() {};

	MaterialData(GLuint amb, GLuint diff, GLuint spec) : // simple
		s_AmbientHandle(amb),
	s_DiffuseHandle(diff),
	s_SpecularHandle(spec),
		s_Shine(1.0f)
	{}

	MaterialData(std::string materialName, GLuint ambient, GLuint diffuse, GLuint specular, float shiny = 1.0f) : // simple + name
		s_Name(materialName),
	s_AmbientHandle(ambient),
	s_DiffuseHandle(diffuse),
	s_SpecularHandle(specular),
	s_Shine(shiny)
	{}

	MaterialData(MaterialData* material) // a simple copy constructor
	{
		s_Name = material->s_Name;

		s_AmbientHandle = material->s_AmbientHandle;
		s_DiffuseHandle = material->s_DiffuseHandle;
		s_SpecularHandle = material->s_SpecularHandle;
		s_EmissiveHandle = material->s_EmissiveHandle;
		s_HeightHandle = material->s_HeightHandle;
		s_NormalsHandle = material->s_NormalsHandle;
		s_ShininessHandle = material->s_ShininessHandle;
		s_OpacityHandle = material->s_OpacityHandle;
		s_DisplacementHandle = material->s_DisplacementHandle;
		s_LightMapHandle = material->s_LightMapHandle;
		s_ReflectionHandle = material->s_ReflectionHandle;

		s_Shine = material->s_Shine;
		s_LightValue = material->s_LightValue;

		s_AmbientName = material->s_AmbientName;
		s_DiffuseName = material->s_DiffuseName;
		s_SpecularName = material->s_SpecularName;
		s_EmissiveName = material->s_EmissiveName;
		s_HeightName = material->s_HeightName;
		s_NormalsName = material->s_NormalsName;
		s_ShininessName = material->s_ShininessName;
		s_OpacityName = material->s_OpacityName;
		s_DisplacementName = material->s_DisplacementName;
		s_LightMapName = material->s_LightMapName;
		s_ReflectionName = material->s_ReflectionName;
	}
};

#endif //__MaterialData_H__
