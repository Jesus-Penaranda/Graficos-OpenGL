#version 330 core

in vec4 frontColor;
out vec4 fragColor;
uniform sampler2D fons;
uniform sampler2D noise1;
uniform float time;
in vec2 vtexCoord;
void main()
{
    vec2 text_mod = vec2(vtexCoord.s + time*0.08, vtexCoord.t + time*0.07);
    vec4 col_ruido = texture(noise1, text_mod);
    vec2 color_rg = col_ruido.rg;
    vec2 pert = color_rg*vec2(0.003, -0.005);
    fragColor = texture(fons, vtexCoord + pert);
}
