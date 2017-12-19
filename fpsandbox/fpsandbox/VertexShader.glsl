#version 330 core
layout (location = 0) in vec3 inPos;
layout (location = 1) in vec3 inNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 Normal;
out vec3 FragPos;

void main()
{
	gl_Position = projection * view * model * vec4(inPos, 1.0);
	FragPos = vec3(model * vec4(inPos, 1.0));
	Normal = mat3(transpose(inverse(model))) * inNormal;  
}