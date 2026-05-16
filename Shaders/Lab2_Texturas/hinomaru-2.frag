#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec2 vtexCoord;
uniform bool classic = false;

void main()
{

    vec2 u = vec2(vtexCoord - vec2(0.5, 0.5));
	float angulo = atan(u.t, u.s);
    float dist = length(vtexCoord.xy - 0.5);
	float res = step(dist, 0.2);
	if (classic)
    {
        if (res == 0) fragColor = vec4(1, 1, 1, 1);
	    else fragColor = vec4(1, 0, 0, 1);
    }
    else
    {
        if (res == 0)
        {
            if (mod(angulo/(3.14 / 16) + 0.5, 2) < 1) fragColor = vec4(1, 0, 0, 1);
            else fragColor = vec4(1, 1, 1, 1);
        }
        else fragColor = vec4(1, 0, 0, 1);
    }
}
