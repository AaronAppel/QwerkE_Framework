// LitMaterial.frag
#version 330 core

// Input
in vec3 t_Normal;
in vec3 t_FragPos;
in vec3 t_VertexPos;
in vec2 t_UV;

// Uniforms
uniform vec3 u_LightPos;
uniform vec3 u_CamPos;

uniform vec3 u_LightColor;

uniform sampler2D u_AmbientTexture; // ambient Handle
uniform sampler2D u_DiffuseTexture; // diffuse Handle
uniform sampler2D u_SpecularTexture; // specular Handle
uniform float u_Shine; // object specific shine

// Output
out vec4 t_FragColor;

void main()
{
    // ambient
	float ambientStrength = 0.2;
    vec3 ambient = ambientStrength * texture(u_AmbientTexture, t_UV).rgb;
	
    // diffuse
	vec3 norm = normalize(t_Normal);
	vec3 lightDir = normalize(u_LightPos - t_FragPos);
	
	float diff = max(dot(norm, lightDir), 0.0);
	
	vec3 diffuse = u_LightColor * diff * texture(u_DiffuseTexture, t_UV).rgb;
	
    // specular
    vec3 viewDir = normalize(u_CamPos - t_FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Shine);
	
	vec3 specular = spec * texture(u_SpecularTexture, t_UV).rgb;
	
	// combine
	t_FragColor = vec4(ambient + diffuse + specular, 1.0);
}