#ifndef _Texture_Asset_H_
#define _Texture_Asset_H_

#include "Asset.h"
#include "../Math/Vector.h"
#include "../../Headers/QwerkE_Global_Constants.h"

#include <string>

typedef unsigned int GLuint;

namespace QwerkE {

    // Might want to limit how tags are created.
    // They should probably just be created by the resource manager.
    class Asset_Tag
    {
    public:
        Asset_Tag();
        ~Asset_Tag();

        std::string GetName() { return m_Name; }

    private:
        std::string m_Name = gc_DefaultStringValue;
        vec3 m_TagColor = vec3(128, 128, 128);
        GLuint m_ThumbnailHandle = 0;
    };

}
#endif // !_Texture_Asset_H_
