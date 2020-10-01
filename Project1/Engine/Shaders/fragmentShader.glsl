#version 450 core

in vec3 Normal;
in vec2 TexCoords;
in vec3 Colour;
in vec3 FragPosition;

out vec4 fColour;





struct Light {
	float diffuse;
	vec3 lightPos;
	float ambient;
	vec3 lightColour;
};
struct Material
{
    float shininess; 
    float transparency;
	sampler2D diffuseMap;
    vec3 ambient; 
    vec3 specular; 
    vec3 diffuse; 
};

uniform Light light;
uniform vec3 viewPosition;
uniform Material material;

void main()
{

    
    vec3 ambient = light.ambient * material.ambient * texture(material.diffuseMap, TexCoords).rgb * light.lightColour;
    
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.lightPos - FragPosition);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = (diff * material.diffuse)* texture(material.diffuseMap, TexCoords).rgb * light.lightColour;
    
	
    vec3 viewDir = normalize(viewPosition - FragPosition);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = material.specular * spec * light.lightColour;

    vec3 result = ambient + diffuse + specular;

    fColour = vec4(result, material.transparency);

}