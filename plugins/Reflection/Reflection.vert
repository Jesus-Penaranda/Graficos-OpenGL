#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 2) in vec3 color;

out vec3 frontColor;

uniform mat4 modelViewProjectionMatrix;

uniform mat4 refMat;

void main() {
    frontColor = color;
    gl_Position = modelViewProjectionMatrix * refMat* vec4(vertex, 1.0);
}
