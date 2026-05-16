#version 330 core

out vec4 fragColor;

in vec3 frontColor;

uniform sampler2D colorMap;

uniform bool mirror;

uniform vec2 size;

void main() {
    if (mirror) {
		vec2 st = (gl_FragCoord.xy - vec2(0.5)) / size;
		fragColor = vec4(0.5 * vec3(0.5), 1) + 0.5*texture(colorMap, st);
	} else {
		fragColor = vec4(frontColor, 1);
	}
}
