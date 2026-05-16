#version 330 core

in vec2 vtexCoord;
in vec4 frontColor;
out vec4 fragColor;
uniform float speed = 0.1;
uniform float time;
uniform sampler2D colorMap;

void main()
{

    vec2 mod = vec2(vtexCoord.s  - time*speed, vtexCoord.t );
    fragColor = frontColor*texture(colorMap, mod);
}
