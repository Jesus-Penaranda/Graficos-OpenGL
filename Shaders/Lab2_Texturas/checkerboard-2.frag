#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec2 vtexCoord;
uniform float n = 8;

void main()
{
    int columna = int(floor(vtexCoord.s*n));
    int fila = int(floor(vtexCoord.t*n));
    int i = columna + fila;
    if (i%2 != 0) fragColor = vec4(0.0, 0.0, 0.0, 1.0);
    else fragColor = vec4(0.8, 0.8 , 0.8, 1);
}
