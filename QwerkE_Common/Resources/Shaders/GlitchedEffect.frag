// LitMaterial.frag
#version 330 core

// Vertex input
in vec3 o_Normal;
in vec3 o_FragPos;
in vec2 o_UV;

// Uniforms
uniform vec3 u_LightPos;
uniform vec3 u_CamPos;

uniform vec3 lightAmbient;
uniform vec3 lightDiffuse;
uniform vec3 lightSpecular;
uniform float shine;

uniform sampler2D u_Texture0; // ambient Handle
uniform sampler2D u_Texture1; // diffuse Handle
uniform sampler2D u_Texture2; // specular Handle

// Output
out vec4 FragColor;

void main()
{
    // ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightAmbient;
  	
    // diffuse
	float diff;
    // vec3 norm = normalize(o_Normal);
    // vec3 lightDir = normalize(u_LightPos - o_FragPos);
    // diff = max(dot(lightDir, norm), 0.0);
	// diff = dot(norm, lightDir);
    vec3 diffuse = diff * lightDiffuse;
	
	/*
	vec4 Result = SurfaceColour * LightColour;
	vec3 Distance;
	Distance = LightPos - VertPos;
	Distance = normalize(Distance);

	float dotProduct;
	dotProduct = dot(Distance, vec3(0,1,0));

	vec4 diff;
	diff = SurfaceColour * LightColour * dotProduct;
	diff.w = 1;
	*/

    // vec3 result = (ambient + diffuse) * texture(u_Texture0, o_UV).rgb;
    FragColor = vec4(diffuse, 1.0);
}
/*
void main()
{
    // ambient
    vec3 ambient = lightAmbient * texture(u_Texture0, o_UV).rgb;

    // diffuse
    vec3 norm = normalize(o_Normal);
    vec3 lightDir = normalize(u_LightPos - o_FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    // vec3 diffuse = lightDiffuse * diff * texture(u_Texture1, o_UV).rgb;
	vec3 diffuse = lightDiffuse * texture(u_Texture1, o_UV).rgb;

    // specular
    vec3 viewDir = normalize(u_CamPos - o_FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shine);
    // vec3 specular = lightSpecular * spec * texture(u_Texture2, o_UV).rgb;
	vec3 specular = lightSpecular * texture(u_Texture2, o_UV).rgb;

	FragColor = vec4(ambient + diffuse + specular, 1.0);
}
*/
