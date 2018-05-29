// PBR1.vert
#version 330 core

// Attribute input
in vec3 a_Position;
in vec2 a_UV;
in vec3 a_Normal;

// Uniforms
uniform mat4 u_WorldMat;
uniform mat4 u_ViewMat;
uniform mat4 u_ProjMat;

// Output
out vec3 t_WorldPos;
out vec2 t_UV;
out vec3 t_Normal;

void main()
{
	// calculate gl_Position value
    gl_Position = u_ProjMat * u_ViewMat * u_WorldMat * vec4(a_Position, 1.0);
	
	// set transfer variable data
	t_WorldPos = vec3(u_WorldMat * vec4(a_Position, 1.0));
	t_Normal = mat3(u_WorldMat) * a_Normal;
	t_UV = a_UV;	
}