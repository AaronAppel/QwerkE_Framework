// Sprite2D.frag
#version 330 core

// Input
in vec2 t_UV;

// Uniforms
uniform sampler2D u_Texture0;

// Output
out vec4 color;

void main()
{
    color = texture(u_Texture0, t_UV);
}