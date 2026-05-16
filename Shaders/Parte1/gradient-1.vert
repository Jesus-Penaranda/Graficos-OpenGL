#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform vec3 boundingBoxMin;
uniform vec3 boundingBoxMax;
vec3 rojo = vec3(1.0, 0.0, 0.0);
vec3 amarillo = vec3(1.0, 1.0, 0.0);
vec3 verde = vec3(0.0, 1.0, 0.0);
vec3 cian = vec3(0.0, 1.0, 1.0);
vec3 azul = vec3(0.0, 0.0, 1.0);

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    vec3 color;
    float y = (vertex.y - boundingBoxMin.y) / (boundingBoxMax.y - boundingBoxMin.y);
    if (y < 0.25) color = mix(rojo, amarillo, fract(y/0.25));
	else if (y < 0.5) color = mix(amarillo, verde, fract(y/0.25));
	else if (y < 0.75) color = mix(verde, cian, fract(y/0.25));
	else if (y < 1) color = mix(cian, azul, fract(y/0.25));
	else color = azul;
    frontColor = vec4(color, 1.0);
    vtexCoord = texCoord;
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
}
