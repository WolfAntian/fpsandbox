#version 330

in vec3 Normal;
in vec3 FragPos;  

uniform vec3 lightPos;  //also cameraPos
uniform vec3 objColor;


out vec4 FragColor;

void main()
{
	vec3 lightColor = vec3(0.7,0.5,0.5);
	vec3 bgColor = vec3(0.1, 0.1, 0.1);

	float distance = length(FragPos - lightPos);
	float visibility = exp(-pow(distance*0.03, 1.5));
	visibility = clamp(visibility, 0.0, 1.0);

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	float specularStrength = 0.5;
	vec3 viewDir = normalize(lightPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm); 
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 16);
	vec3 specular = specularStrength * spec * lightColor;  

	vec3 ambient = 0.2 * lightColor;
	vec3 result = (ambient + diffuse + specular) * objColor;
	FragColor = vec4(result,1.0f);
	FragColor = mix(vec4(bgColor,1.0),FragColor, visibility);
}