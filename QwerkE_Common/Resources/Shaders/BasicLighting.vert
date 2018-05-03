// Basic3D.vert
#version 330 core

attribute vec3 a_Position;
attribute vec3 a_Normal;

uniform mat4 u_WorldMat;
uniform mat4 u_ViewMat;
uniform mat4 u_ProjMat;

out vec3 v_Normal;
out vec3 v_FragmentPos;

void main()
{
    gl_Position = u_ProjMat * u_ViewMat * u_WorldMat * vec4(a_Position, 1.0);
	
	v_FragmentPos = vec3(u_WorldMat * vec4(a_Position, 1.0f));
	v_Normal = mat3(transpose(inverse(u_WorldMat))) * a_Normal;
}