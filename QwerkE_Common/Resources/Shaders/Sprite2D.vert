// Sprite2D.vert
#version 330 core

// Input
in vec3 a_Position;
in vec2 a_UV;

// Uniforms
uniform mat4 u_Transform;

// Output
out vec2 t_UV;

void main()
{
    gl_Position = u_Transform * vec4(a_Position, 1.0);

	// Output
	t_UV = a_UV;
}