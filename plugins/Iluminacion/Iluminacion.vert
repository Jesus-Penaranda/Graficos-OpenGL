#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;

out vec3 v_vertex;
out vec3 v_normal;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;

void main() {

    v_vertex = (modelViewMatrix * vec4(vertex, 1.0)).xyz;

    v_normal = normalize(normalMatrix * normal);

    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
}
