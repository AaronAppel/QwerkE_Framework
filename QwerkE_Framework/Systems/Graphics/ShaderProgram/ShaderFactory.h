#ifndef __SHADERFACTORY_H__
#define __SHADERFACTORY_H__

////* Work in progress *////

//enum eShaderTypes {};
// NOTE: add \n to beginning of string ex."\nText"
#include "../../Graphics_Header.h"
#include "../OpenGLHelpers.h"

#include <string>

class ShaderFactory
{
public:
	ShaderFactory() {}
	~ShaderFactory() {}

	ShaderProgram* CreateShader(eShaderTypes type);
	ShaderProgram* CreateShader(const char* vertFileDir, const char* fragFileDir, const char* geoFileDir);

	const char* CreateVertexShader(eShaderTypes shaderName);
	const char* CreateFragmentShader(eShaderTypes shaderName);
	const char* CreateGeometryShader(eShaderTypes shaderName);

	void SetVertName(eShaderTypes shaderType, std::string &shaderString);
	void SetFragName(eShaderTypes shaderType, std::string &shaderString);
	void SetGeoName(eShaderTypes shaderType, std::string &shaderString);
	void SetVersion(std::string &shaderString);

	void OpenMain(std::string &shaderString);
	void CloseMain(std::string &shaderString);

	/* Getters + Setters */
	/* Getters */
	const char*  GetAttributePrefix() { return m_AttributePrefix; };
	const char*  GetUniformPrefix() { return m_UniformPrefix; };
	const char*  GetTransferPrefix() { return m_TransferPrefix; };

	/* Setters */
	void SetPrefixes(const char* attr, const char* unif, const char* trans);

private:
	/* Write Shader functions */
	// Basic3D
	std::string Basic3DShaderVert(std::string vertString);
	std::string Basic3DShaderFrag(std::string fragString);
	// Basic2D
	std::string Basic2DShaderVert(std::string vertString);
	std::string Basic2DShaderFrag(std::string fragString);
	// LitMaterial
	std::string LitMaterialVert(std::string vertString);
	std::string LitMaterialFrag(std::string fragString);

	/* Values */
	const char* m_AttributePrefix = Helper_GetAttributePrefix(); // = blue_GetAttributePrefix(); // TODO: a_ probably works for attributes
	const char* m_UniformPrefix = Helper_GetUniformPrefix(); // = blue_GetUniformPrefix();
	const char* m_TransferPrefix = Helper_GetTransferPrefix(); // = blue_GetTransferPrefix(); // t_ means the variable is being transferred from one shader to another

	/* Add Shader Variables */
	// structs
	void AddMaterialStruct(std::string &string);
	void AddUniformMaterialStruct(const char* name, std::string &string);

	void AddLightStruct(std::string &string);

	// attributes
	// TODO: Try to reuse the following functions to reduce duplicating code
	void AddAttributeInt(const char* name, std::string &string);

	void AddAttributeFloat(const char* name, std::string &string);
	void AddAttributeVec2(const char* name, std::string &string);
	void AddAttributeVec3(const char* name, std::string &string);
	void AddAttributeVec4(const char* name, std::string &string);

	void AddAttributeMat2(const char* name, std::string &string);
	void AddAttributeMat3(const char* name, std::string &string);
	void AddAttributeMat4(const char* name, std::string &string);

	// uniforms
	void AddUniformInt(const char* name, std::string &string);

	void AddUniformFloat(const char* name, std::string &string);
	void AddUniformVec2(const char* name, std::string &string);
	void AddUniformVec3(const char* name, std::string &string);
	void AddUniformVec4(const char* name, std::string &string);

	void AddUniformMat2(const char* name, std::string &string);
	void AddUniformMat3(const char* name, std::string &string);
	void AddUniformMat4(const char* name, std::string &string);

	void AddUniformSampler2D(const char* name, std::string string);

	void AddUniformTexture(int* count, std::string string);

	// input
	void AddInputInt(const char* name, std::string &string);

	void AddInputFloat(const char* name, std::string &string);
	void AddInputVec2(const char* name, std::string &string);
	void AddInputVec3(const char* name, std::string &string);
	void AddInputVec4(const char* name, std::string &string);

	void AddInputMat2(const char* name, std::string &string);
	void AddInputMat3(const char* name, std::string &string);
	void AddInputMat4(const char* name, std::string &string);

	// output
	void AddOutputInt(const char* name, std::string &string);

	void AddOutputFloat(const char* name, std::string &string);
	void AddOutputVec2(const char* name, std::string &string);
	void AddOutputVec3(const char* name, std::string &string);
	void AddOutputVec4(const char* name, std::string &string);

	void AddOutputMat2(const char* name, std::string &string);
	void AddOutputMat3(const char* name, std::string &string);
	void AddOutputMat4(const char* name, std::string &string);
};

#endif //__SHADERFACTORY_H__
