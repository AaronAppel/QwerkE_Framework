#pragma once

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

        void Init()
        {
            // #TODO Review and remove unnecessary comments

            glGenFramebuffers(1, &framebuffer);
            glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

            glGenTextures(1, &textureColorbuffer);
            glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Renderer::g_WindowWidth, Renderer::g_WindowHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);

            glGenRenderbuffers(1, &rbo);
            glBindRenderbuffer(GL_RENDERBUFFER, rbo);

            // Use a single render buffer object for both a depth AND stencil buffer.
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, Renderer::g_WindowWidth, Renderer::g_WindowHeight);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // Now attach the render buffer

            // Now that we actually created the frame buffer and added all attachments, we want to check if it is actually complete now
            if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
                int bp = 1;// cout << "ERROR::FRAMEBUFFER:: Frame buffer is not complete!" << endl; // #TODO Review error handling
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

        void Bind()
        {
            glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
        }

        void UnBind()
        {
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
