#version 330 core

in vec2 vtexCoord;

uniform sampler2D explosion;
uniform float time;

out vec4 fragColor;

void main()
{
    const float slice = 1.0 / 30.0;
    float frame = floor(mod(time / slice, 48.0));

    float fila = floor(frame / 8.0);
    float columna = mod(frame, 8.0);

    vec2 tamanoFrame = vec2(1.0 / 8.0, 1.0 / 6.0);

    vec2 texCoordEscalado = vtexCoord*tamanoFrame;

    float offsetX = columna*tamanoFrame.x;
    float filaInvertida = 5.0 - fila;
    float offsetY = filaInvertida * tamanoFrame.y;

    vec2 offset = vec2(offsetX, offsetY);
    vec2 uv_final = offset + texCoordEscalado;
    vec4 color = texture(explosion, uv_final);
    fragColor = color*color.a;
}
