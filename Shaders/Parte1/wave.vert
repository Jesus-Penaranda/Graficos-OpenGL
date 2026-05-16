#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

const float pi = 3.141592;
uniform float amp = 0.5;
uniform float freq = 0.25;
uniform float time;

mat3 rotate_x(float angle)
{
    float c = cos(angle);
    float s = sin(angle);
    return mat3(vec3(1, 0, 0), vec3(0, c, s), vec3(0, -s , c));
}

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(color,1.0);
    vec3 vecmod = rotate_x((amp*sin(2*pi*freq*time + vertex.y)))*vertex;
    vtexCoord = texCoord;
    gl_Position = modelViewProjectionMatrix * vec4(vecmod, 1.0);
}
