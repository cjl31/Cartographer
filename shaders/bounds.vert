#version 330 core
layout(location = 0) in vec3 aPos;

uniform mat4 WorldTransform;
uniform mat4 LocalTransform;

void main()
{
	gl_Position = WorldTransform * LocalTransform * vec4(aPos, 1.0);
}