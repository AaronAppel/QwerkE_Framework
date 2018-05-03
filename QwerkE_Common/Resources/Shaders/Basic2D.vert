// Basic2D.vert
#version 330 core

// Attribute input
in vec3 a_Position;

// Uniforms
// Output

void main()
{
    gl_Position = vec4(a_Position, 1.0);
}