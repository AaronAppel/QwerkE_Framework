#pragma once

#include "../../Libraries/glew/GL/glew.h"
#include "../../../Headers/QwerkE_Enums.h"

#include <string>

namespace QwerkE {

    struct MaterialComponent
    {
        MaterialComponent() = default;
        MaterialComponent(std::string name, GLuint handle) :
            s_TextureName(name),
            s_Handle(handle) {} // #TODO Review formatting

        eMaterialMaps s_Type = eMaterialMaps::MatMap_Null;

        std::string s_TextureName = gc_DefaultStringValue;

        GLuint s_Handle = 0;
    };

}
