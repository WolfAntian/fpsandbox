#version 330 core
layout (location = 0) in vec3 pos;

uniform mat4 transform;


void main()
{
	gl_Position = transform * vec4(pos.x, pos.y, pos.y, 1.0);
}