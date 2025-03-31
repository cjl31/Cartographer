#version 330 core
uniform vec3 fragColor;

out vec4 outColor;

void main()
{
    outColor = vec4(fragColor.r, fragColor.g, fragColor.b, 1);
}
