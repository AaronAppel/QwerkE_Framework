// Basic3D.frag
#version 330 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

uniform Material u_Material;

uniform vec4 u_ObjectColour;
uniform vec4 u_LightColor;

uniform vec3 u_LightPos;
uniform vec3 u_CamPos;

in vec3 v_Normal;
in vec3 v_FragmentPos;

out vec4 o_Colour;

void main()
{
    // Ambient
    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * u_LightColor.xyz;

    // Diffuse
    vec3 norm = normalize(v_Normal);
    vec3 lightDir = normalize(u_LightPos - v_FragmentPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * u_LightColor.xyz;

    // Specular
    float specularStrength = 0.5f;
    vec3 viewDir = normalize(u_CamPos - v_FragmentPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 256);
    vec3 specular = specularStrength * spec * u_LightColor.xyz;

    vec3 result = (ambient + diffuse + specular) * u_ObjectColour.xyz;
    o_Colour = vec4(result, 1.0f);
}

/*
void main()
{
	// ambient
	float ambientStrength = 0.1f;
	vec4 ambientLight = ambientStrength * u_LightColor;

	// diffuse
	vec3 normal = normalize(i_Normal);
	vec3 lightDir = normalize(u_LightPos - i_FragmentPos);
	float diff = max(dot(normal, lightDir), 0.0);
	vec4 diffuse = diff * u_LightColor;

	// specular
	float specularStrength = 0.5f;
	vec3 viewDir = normalize(u_CamPos - i_FragmentPos);
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec4 specular = specularStrength * spec * u_LightColor;

	vec4 result = (ambientLight + diffuse + specular) * u_ObjectColour;
	color = result;
}
*/