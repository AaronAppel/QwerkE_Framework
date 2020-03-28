#ifndef _RenderComponent_H_
#define _RenderComponent_H_

#include "Component.h"
#include "../../../Graphics/DataTypes/Renderable.h"

#include <vector>
#include <string>

namespace QwerkE {

    class ShaderProgram;
    class Material;
    class Mesh;

    class RenderComponent : public Component
    {
    public:
        RenderComponent();
        RenderComponent(const char* objectRecipe);
        RenderComponent(const char* shaderName, const char* materialName, const char* meshName);
        ~RenderComponent();

        void GenerateSchematic();

        void Setup(const char* shaderName, const char* materialName, const char* meshName);
        // void Clear();

        void AppendEmptyRenderables(int count);
        void AddRenderable(Renderable renderable);

        // Getters + Setters //
        // Getters
        std::string GetSchematicName() const { return m_SchematicName; }
        std::vector<Renderable>* GetRenderableList() { return &m_RenderableList; } // Change to SeeRenderablesList()
        const std::vector<Renderable>* SeeRenderableList() const { return &m_RenderableList; }

        // Setters
        void SetSchematicName(std::string name) { m_SchematicName = name; }
        void SetNameAtIndex(unsigned int index, std::string name);
        void SetShaderAtIndex(unsigned int index, ShaderProgram* shader);
        void SetMaterialAtIndex(unsigned int index, Material* material);
        void SetMeshAtIndex(unsigned int index, Mesh* mesh);

        const std::vector<Renderable>* LookAtRenderableList() { return &m_RenderableList; }

    private:
        std::string m_SchematicName = "None";
        std::vector<Renderable> m_RenderableList;
    };

}
#endif // !_RenderComponent_H_
