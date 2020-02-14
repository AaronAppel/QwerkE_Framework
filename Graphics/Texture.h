#ifndef _Texture_H_
#define _Texture_H_

#include "../Libraries/glew/GL/glew.h"

#include <string>

namespace QwerkE {

    struct Texture
    {
    public:

        Texture() {}
        ~Texture() {}

#ifdef OpenGL
        Texture(GLuint handle) : s_Handle(handle) {}
        GLuint s_Handle = 0;
#else
        unsigned int s_Handle = 0;
#endif

        std::string s_Name = gc_DefaultStringValue;
    };

}
#endif // !_Texture_H_
