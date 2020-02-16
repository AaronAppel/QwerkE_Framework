#ifndef _Material_H_
#define _Material_H_

#include "../Libraries/glew/GL/glew.h"
#include "../Systems/FileSystem/FileIO/FileUtilities.h"
#include "../GraphicsUtilities/GraphicsHelpers.h"
#include "../Headers/QwerkE_Enums.h"
#include "Texture.h"

#include <string>
#include <map>

namespace QwerkE {

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
            if (type < eMaterialMaps::MatMap_Max && (int)type > -1)
            {
                m_Components[type] = comp;
            }
        }

        void SetTexture(Texture* comp, eMaterialMaps type)
        {
            if (comp && (int)type > -1 && type < eMaterialMaps::MatMap_Max)
            {
                m_Components[type] = comp;
            }
        }

        void SetMaterialName(std::string name) { m_Name = name; }

    private:
        std::string m_Name = gc_DefaultStringValue;
        std::map<eMaterialMaps, Texture*> m_Components;

        // TODO: Create a basic colour component just for specific uses

        // other data needed by shaders
        // float s_Shine = 0.5f;
        // vec4 s_LightValue = vec4(1,1,1,1);
    };

}
#endif //!_Material_H_
