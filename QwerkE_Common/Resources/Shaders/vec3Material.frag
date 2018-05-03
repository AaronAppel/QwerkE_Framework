// LitMaterial.frag
#version 330 core

// Vertex input
in vec3 o_Normal;
in vec3 o_FragPos;

// Uniforms
uniform vec3 u_LightPos;
uniform vec3 u_ViewPos;
uniform vec3 u_LightColor;
uniform vec3 u_ObjectColor;

uniform vec3 ambientCol;
uniform vec3 diffuseCol;
uniform vec3 specularCol;
uniform float shine;

// Output
out vec4 FragColor;

void main()
{
	vec3 col = vec3(1,1,1);
    // ambient
    vec3 ambient = u_LightColor * ambientCol;

    // diffuse
    vec3 norm = normalize(o_Normal);
    vec3 lightDir = normalize(u_LightPos - o_FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = u_LightColor * (diff * diffuseCol);

    // specular
    vec3 viewDir = normalize(u_ViewPos - o_FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shine);
    vec3 specular = u_LightColor * (spec * specularCol);

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}