#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec2 vtexCoord;

void main()
{

    vec4 colorRojo = vec4(1.0, 0.0, 0.0, 1.0);
    vec4 colorBlanco = vec4(1.0, 1.0, 1.0, 1.0);

    float dist = length(vtexCoord.xy - 0.5);

    float radio = 0.2;
    float suavizado = 0.005;

    float edge0 = radio - suavizado;
    float edge1 = radio + suavizado;

    float res = smoothstep(edge0, edge1, dist);

    fragColor = mix(colorRojo, colorBlanco, res);
}
