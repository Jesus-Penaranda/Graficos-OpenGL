#version 330 core

in vec4 frontColor;
out vec4 fragColor;

uniform int n = 2;

void main()
{
    if (mod(gl_FragCoord.y, float(n)) != 0.0) discard;

    fragColor = frontColor;
}
