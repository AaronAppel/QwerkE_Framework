// LitMaterial.vert
#version 330 core

// Attribute input
in vec3 i_Position;
in vec3 i_Normal;

// Uniforms
uniform mat4 u_WorldMat;
uniform mat4 u_ViewMat;
uniform mat4 u_ProjMat;

// Output
out vec3 o_FragPos;
out vec3 o_Normal;

void main()
{
	// gl_Position
    gl_Position = u_ProjMat * u_ViewMat * u_WorldMat * vec4(i_Position, 1.0);

	// Output
    o_FragPos = vec3(u_WorldMat * vec4(i_Position, 1.0));
    o_Normal = mat3(transpose(inverse(u_WorldMat))) * i_Normal;
}