// TestShader.frag
#version 330 core

uniform vec4 u_ObjectColor;

out vec4 t_Color;

void main()
{
    t_Color = vec4(1,0,1,1);//u_ObjectColor;//
}