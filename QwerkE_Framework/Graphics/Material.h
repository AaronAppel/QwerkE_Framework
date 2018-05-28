#ifndef _Material_H_
#define _Material_H_

#include "../../../QwerkE_Common/Libraries/glew/GL/glew.h"
#include "../../../QwerkE_Common/Utilities/PrintFunctions.h"
#include "../../../QwerkE_Common/Utilities/FileIO/FileUtilities.h"
#include "GraphicsUtilities/GraphicsHelpers.h"
#include "../QwerkE_Framework/QwerkE_Framework/QwerkE_Enums.h"
#include "Texture.h"

#include <string>
#include <map>

class Material
{
public:
	Material() {};

	Material(const char* materialSchematicPath)
	{
		LoadMaterialSchematic(materialSchematicPath, this);
	}

	Material(const std::map<eMaterialMaps, Texture*>& textures)
	{
		m_Components.clear();
		m_Components = textures; // TODO: Check how data is copied. Shallow copy should work.
	}

	Material(Material* material) // a simple copy constructor
	{
		// shallow copy components to not duplicate them
		const std::map<eMaterialMaps, Texture*>* othercomponents = material->SeeMaterials();
		m_Components = *othercomponents; // TODO: Check how data is copied. Shallow copy should work.
	}

	int NumberOfMaterials() { return m_Components.size(); }

	const std::map<eMaterialMaps, Texture*>* SeeMaterials() const { return &m_Components; }

	std::string GetMaterialName() { return m_Name; }

	Texture* GetMaterialByType(eMaterialMaps type)
	{
		if (m_Components.find(type) != m_Components.end())
		{
			return m_Components[type];
		}
		else return nullptr;
	}

	void AddTexture(Texture* comp, eMaterialMaps type)
	{
		// only add if type is not already assigned
		if (type < eMaterialMaps::MatMap_Null && (int)type > -1)
		{
			m_Components[type] = comp;
		}
	}

	void SetTexture(Texture* comp, eMaterialMaps type)
	{
		if (comp && (int)type > - 1 && type < eMaterialMaps::MatMap_Null)
		{
			m_Components[type] = comp;
		}
	}

	void SetMaterialName(std::string name) { m_Name = name; }

private:
	std::string m_Name = "Uninitialized";
	std::map<eMaterialMaps, Texture*> m_Components;

	// TODO: Create a basic colour component just for specific uses

	// other data needed by shaders
	// float s_Shine = 0.5f;
	// vec4 s_LightValue = vec4(1,1,1,1);
};

#endif //!_Material_H_
