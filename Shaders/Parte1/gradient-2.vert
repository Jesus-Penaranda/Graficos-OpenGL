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
const vec3 rojo = vec3(1, 0, 0);
const vec3 amarillo = vec3(1, 1, 0);
const vec3 verde = vec3(0, 1, 0);
const vec3 cian = vec3(0, 1, 1);
const vec3 azul = vec3(0, 0, 1);

void main()
{

    vec3 N = normalize(normalMatrix * normal);
    vtexCoord = texCoord;
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);

    float y = gl_Position.y / gl_Position.w;
	vec3 color;
	if (y < -0.5) color = mix(rojo, amarillo, fract(y/0.5));
	else if (y < 0) color = mix(amarillo, verde, fract(y/0.5));
	else if (y < 0.5) color = mix(verde, cian, fract(y/0.5));
	else if (y < 1) color = mix(cian, azul, fract(y/0.5));
	else color = azul;
	frontColor = vec4(color, 1.0);
}
