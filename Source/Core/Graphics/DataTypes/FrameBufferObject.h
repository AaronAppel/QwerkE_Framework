#ifndef _FrameBufferObject_H_
#define _FrameBufferObject_H_

#include "../Libraries/glew/GL/glew.h"

#include "../Renderer.h"

namespace QwerkE {

    class FrameBufferObject
    {
    public:
        FrameBufferObject()
        {
            framebuffer = 0;
            textureColorbuffer = 0;
            rbo = 0;
        }

        ~FrameBufferObject() {}

        void Init()
        {
            // framebuffer configuration
            // -------------------------

            glGenFramebuffers(1, &framebuffer);
            glBindFramebuffer(GL_FRAMEBUFFER, framebuffer); // bind
            // create a color attachment texture
            glGenTextures(1, &textureColorbuffer);
            glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Renderer::g_WindowWidth, Renderer::g_WindowHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);
            // create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
            glGenRenderbuffers(1, &rbo);
            glBindRenderbuffer(GL_RENDERBUFFER, rbo);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, Renderer::g_WindowWidth, Renderer::g_WindowHeight); // use a single renderbuffer object for both a depth AND stencil buffer.
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it
                                                                                                          // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
            if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
                int bp = 1;// cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << endl;
            glBindFramebuffer(GL_FRAMEBUFFER, 0); // unbind
            // TODO: Unbind texture?
        }

        void Bind()
        {
            glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
        }

        void UnBind()
        {
            // now bind back to default framebuffer and draw a quad plane with the attached framebuffer color texture
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

        void Reset() { textureColorbuffer = 0; };

        GLuint GetTextureID() { return textureColorbuffer; };

    private:
        GLuint framebuffer = 0;
        GLuint textureColorbuffer = 0;
        GLuint rbo = 0;
    };

}
#endif //!_FrameBufferObject_H_
