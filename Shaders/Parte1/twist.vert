#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;
uniform float time;

mat3 rotate_y(float angle)
{
    float c = cos(angle);
    float s = sin(angle);
    return mat3(c, 0, -s, 0, 1, 0, s, 0, c);
}

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    float angulo = 0.4*(vertex.y)*sin(time);
    vec3 vertex_mod = rotate_y(angulo)*vertex;
    frontColor = vec4(color, 1.0);
    vtexCoord = texCoord;
    gl_Position = modelViewProjectionMatrix * vec4(vertex_mod, 1.0);
}
