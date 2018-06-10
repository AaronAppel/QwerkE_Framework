// null_shader.vert
#version 330 core

// Attribute input
in vec3 a_Position;

// Uniforms
uniform mat4 u_WorldMat;
uniform mat4 u_ViewMat;
uniform mat4 u_ProjMat;

// Output

void main()
{
    gl_Position = u_ProjMat * u_ViewMat * u_WorldMat * vec4(a_Position, 1.0);
}