#pragma once

// #TODO Move code to a rendering manager or rendering library header. Deprecate this file

#ifdef OpenGL
GLuint gc_NullHandleValue = 0; // For textures, shaders, etc
#else
#pragma warning "Define rendering engine!"
#endif // OpenGL
