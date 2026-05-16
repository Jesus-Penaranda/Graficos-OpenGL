#version 330 core

uniform sampler2D jungla;

in vec4 frontColor;
out vec4 fragColor;

uniform vec2 mousePosition;

uniform vec2 viewport;

uniform float magnific = 3;

in vec2 vtexCoord;

vec4 blurImage( in vec2 coords )
{
    float Pi = 6.28318530718;
    float Directions = 16.0;
    float Quality = 8.0;
    float Size = 10.0;

    vec2 Radius = Size/viewport;

    vec4 Color = texture(jungla, coords);
    for( float d=0.0; d<Pi; d+=Pi/Directions)
    {
        float cd = cos(d);
        float sd = sin(d);
		for(float i=1.0/Quality; i<=1.0; i+=1.0/Quality)
        {
			Color += texture(jungla, coords+vec2(cd,sd)*Radius*i);
        }
    }

    Color /= Quality * Directions - 15.0;
    return  Color;
}

void main()
{
    vec4 col;
    float d = distance(vec2(mousePosition.x+80, mousePosition.y), gl_FragCoord.xy);
    float d2 = distance(vec2(mousePosition.x-80, mousePosition.y), gl_FragCoord.xy);

    if (d > 105 && d2 > 105) col = blurImage(vtexCoord);
    else if (d < 100 || d2 < 100) {

        vec2 vec_frag = vec2(gl_FragCoord.x-mousePosition.x, gl_FragCoord.y-mousePosition.y);
        vec_frag = normalize(vec_frag);

        float d_real = distance(gl_FragCoord.xy, mousePosition);
        float d_tex = d_real/magnific;

        vec2 res = mousePosition + vec_frag*d_tex;
        res /= viewport;

    	col = texture(jungla, res);
    }
    else col = vec4(0.0, 0.0, 0.0, 1.0);

    fragColor = col;
}
