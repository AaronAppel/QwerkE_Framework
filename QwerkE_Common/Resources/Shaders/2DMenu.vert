// 2DMenu.vert
#version 330 core

in vec3 i_Position;

uniform mat4 u_Transform;

void main()
{
	gl_Position = vec4(u_Transform * vec4(i_Position, 1.0));
}