// Basic2D.frag
#version 330 core

// Input

// Uniform
uniform vec4 u_Colour;

// Output
out vec4 t_Colour;

void main()
{
    t_Colour = u_Colour;
}