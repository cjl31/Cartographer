#version 330 core
layout(location = 0) in vec3 aPos;

uniform vec2 offsets[2000];
uniform mat4 WorldTransform;
uniform mat4 LocalTransform;

void main()
{
	vec2 offset = offsets[gl_InstanceID];
	gl_Position = WorldTransform * LocalTransform * vec4(aPos + vec3(offset, 0.0), 1.0);
}