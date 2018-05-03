// LitMaterial.vert
#version 330 core

// Attribute input
in vec3 a_Position;
in vec3 a_Normal;
in vec2 a_UV;

// Uniforms
uniform mat4 u_WorldMat;
uniform mat4 u_ViewMat;
uniform mat4 u_ProjMat;

// Output
out vec3 t_FragPos;
out vec3 t_VertexPos;
out vec3 t_Normal;
out vec2 t_UV;

void main()
{
	// gl_Position
    gl_Position = u_ProjMat * u_ViewMat * u_WorldMat * vec4(a_Position, 1.0);

	// Output
    t_FragPos = vec3(u_WorldMat * vec4(a_Position, 1.0));
    t_Normal = mat3(transpose(inverse(u_WorldMat))) * a_Normal;
	t_UV = a_UV;
	
	t_VertexPos = (u_WorldMat * vec4(a_Position, 1.0)).xyz;
}