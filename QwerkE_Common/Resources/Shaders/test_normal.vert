#version 330 core
in vec3 a_Position;
in vec3 a_Normal;
in vec2 a_UV;
in vec3 aTangent;
in vec3 aBitangent;

out VS_OUT {
    vec3 FragPos;
    vec2 TexCoords;
    vec3 TangentLightPos;
    vec3 TangentViewPos;
    vec3 TangentFragPos;
} vs_out;

uniform mat4 u_ProjMat;
uniform mat4 u_ViewMat;
uniform mat4 u_WorldMat;

uniform vec3 u_LightPos;
uniform vec3 u_CamPos;

void main()
{
    vs_out.FragPos = vec3(u_WorldMat * vec4(aPos, 1.0));   
    vs_out.TexCoords = a_UV;
    
    mat3 normalMatrix = transpose(inverse(mat3(u_WorldMat)));
    vec3 T = normalize(normalMatrix * aTangent);
    vec3 N = normalize(normalMatrix * a_Normal);
    T = normalize(T - dot(T, N) * N);
    vec3 B = cross(N, T);
    
    mat3 TBN = transpose(mat3(T, B, N));    
    vs_out.TangentLightPos = TBN * u_LightPos;
    vs_out.TangentViewPos  = TBN * u_CamPos;
    vs_out.TangentFragPos  = TBN * vs_out.FragPos;
        
    gl_Position = u_ProjMat * u_ViewMat * u_WorldMat * vec4(aPos, 1.0);
}