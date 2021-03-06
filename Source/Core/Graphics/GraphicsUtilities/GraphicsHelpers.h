#ifndef _Graphics_Helpers_H_
#define _Graphics_Helpers_H_

//////////////////////////////
// GraphicsHelpers.h
// Defines an interface for graphics utility functions such as texture loading.
// The function bodies vary based on graphics libraries.
//////////////////////////////

#include "../DataTypes/FrameBufferObject.h"

namespace QwerkE {

    // TODO: Can I just #macro the functions to avoid a stack frame?
    void CheckAllGraphicsErrors();
    void CheckGraphicsErrors();
    void CheckGraphicsErrors(char* file, int line);
    void CheckGraphicsErrors(const char* file, int line);

    GLuint Load2DTexture(const char* filename, bool flipVertically = 0);
    GLuint LoadCubeMapTexture(const char* filename);

    // GLuint Duplicate2DTexture(GLuint handle, int w, int h, int x, int y);
    GLuint CopyFBOToTexture(FrameBufferObject& handle, int w, int h, int x = 0, int y = 0);

    class RenderComponent;
    void SaveObjectSchematic(RenderComponent* rComp);
    RenderComponent* LoadRenderComponentFromSchematic(const char* schematicPath);
    void LoadRenderComponentFromSchematic(const char* schematicPath, RenderComponent* renderComponent);

    class Material;
    void SaveMaterialSchematic(Material* material);
    void LoadMaterialSchematic(const char* schematicPath, Material* material);
    Material* LoadMaterialSchematic(const char* schematicPath);

    class Model;
    void SaveMaterialSchematic(Material* material);
    Material* LoadMaterialSchematic(const char* schematicPath);

    class ShaderProgram;
    void SaveShaderSchematic(ShaderProgram* shader);
    ShaderProgram* LoadShaderSchematic(const char* schematicPath);

    // TODO: Move to a better place
    // TODO: Pick a standard (input OR attribute)
    // Shader variable prefixes

    constexpr const char* AttributePrefix = "a_";
    constexpr const char* InputPrefix = "i_";
    constexpr const char* UniformPrefix = "u_";
    constexpr const char* TransferPrefix = "t_";
    constexpr const char* VaryingPrefix = "v_";

}
#endif // _Graphics_Helpers_H_
