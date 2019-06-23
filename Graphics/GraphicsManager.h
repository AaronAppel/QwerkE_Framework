// TODO: Move code to a rendering manager or rendering library header

#ifndef _QwerkE_Graphics_Manager_H_
#define _QwerkE_Graphics_Manager_H_

#ifdef OpenGL
GLuint gc_NullHandleValue = 0; // For textures, shaders, etc
#else
#pragma warning "Define rendering engine!"
#endif // OpenGL


#endif //!_QwerkE_Graphics_Manager_H_
