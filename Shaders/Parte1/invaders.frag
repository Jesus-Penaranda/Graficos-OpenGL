#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec2 vtexCoord;

uniform sampler2D colormap;
const float PI = 3.1415;
const mat2 rot = mat2(cos(PI/2.), sin(PI/2.), -sin(PI/2.), cos(PI/2.));

void main()
{
    float x = floor(vtexCoord.s * 12.);
    float y = floor(vtexCoord.t * 12.);
    vec2 vtexCoord2 = vtexCoord * rot;
    vec2 vtexCoord3 = vtexCoord * rot * rot;
    vec2 vtexCoord4 = vtexCoord * rot * rot * rot;
    float ntcS = fract(vtexCoord.s * 12.);
    float ntcT = fract(vtexCoord.t * 12.);
    float ntcS2 = fract(vtexCoord2.s * 12.);
    float ntcT2 = fract(vtexCoord2.t * 12.);
    float ntcS3 = fract(vtexCoord3.s * 12.);
    float ntcT3 = fract(vtexCoord3.t * 12.);
    float ntcS4 = fract(vtexCoord4.s * 12.);
    float ntcT4 = fract(vtexCoord4.t * 12.);
    vec2 bicho1 = vec2(ntcS / 4. + 0./4., ntcT/ 4 + 0./4.);
    vec2 bicho2 = vec2(ntcS / 4. + 1./4., ntcT/ 4 + 0./4);
    vec2 bicho3 = vec2(ntcS / 4. + 2./4., ntcT/ 4 + 0./4);
    vec2 escudos = vec2(ntcS / 4. + 3./4., ntcT/ 4 + 0./4);
    vec2 bicho4 = vec2(ntcS / 4. + 0./4., ntcT/ 4 + 1./4);
    vec2 bicho5 = vec2(ntcS / 4. + 1./4., ntcT/ 4 + 1./4);
    vec2 bicho6 = vec2(ntcS / 4. + 2./4., ntcT/ 4 + 1./4);
    vec2 bicho7 = vec2(ntcS / 4. + 0./4., ntcT/ 4 + 2./4);
    vec2 bicho8 = vec2(ntcS / 4. + 0./4., ntcT/ 4 + 3./4);
    vec2 bicho9 = vec2(ntcS / 4. + 3./4., ntcT/ 4 + 3./4);

    vec2 arma = vec2(ntcS / 4. + 3./4., ntcT/ 4 + 1./4);

    if (x == 4 && y == 1)
        fragColor = texture(colormap, arma);
    else if ((x == 1 || x == 5 || x == 10 ) && y == 2)
        fragColor = texture(colormap, escudos);
    else if (y == 3)
        fragColor = texture(colormap, bicho1);
    else if (y == 4)
        fragColor = texture(colormap, bicho2);
    else if (y == 5)
        fragColor = texture(colormap, bicho3);
    else if (y == 6)
        fragColor = texture(colormap, bicho4);
    else if (y == 7)
        fragColor = texture(colormap, bicho5);
    else if (y == 8)
        fragColor = texture(colormap, bicho6);
    else if (y == 9)
        fragColor = texture(colormap, bicho7);
    else if (y == 10)
        fragColor = texture(colormap, bicho8);
    else if (y == 11)
        fragColor = texture(colormap, bicho9);
    else
        fragColor = vec4(0.0,0.0,0.0,1.0);
}
