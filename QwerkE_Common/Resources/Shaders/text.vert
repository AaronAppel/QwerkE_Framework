#version 330 core
in vec4 a_vertex; // <vec2 pos, vec2 tex>
out vec2 t_TexCoords;

uniform mat4 u_projection;

void main()
{
    gl_Position = u_projection * vec4(a_vertex.xy, 0.0, 1.0);
    t_TexCoords = a_vertex.zw;
}  