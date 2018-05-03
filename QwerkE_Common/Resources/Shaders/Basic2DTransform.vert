// Basic2D.vert
#version 330 core

in vec3 i_Position;
uniform mat4 u_Transform;

void main()
{
    gl_Position = u_Transform * vec4(i_Position, 1.0);
}