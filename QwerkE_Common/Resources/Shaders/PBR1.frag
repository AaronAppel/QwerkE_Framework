// PBR1.frag
#version 330 core

// Transfer
in vec3 t_WorldPos;
in vec2 t_UV;
in vec3 t_Normal;

// Output
out vec4 t_FragColor;

void main()
{
	t_FragColor = vec4(1,1,1,1);
}
