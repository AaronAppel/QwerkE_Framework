// Basic2DTex.vert
#version 330 core

// Input
in vec3 a_Position;
in vec2 a_UV;

// Uniforms

// Output
out vec2 t_UV;

void main()
{
    gl_Position = vec4(a_Position, 1.0);

	t_UV = a_UV;
}