#version 330 core
layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;
uniform float time;

out vec4 frontColor;

void main()
{

    float t_period = mod(time, 3.5);

    vec3 pos_origen = vec3(0.0);
    vec3 pos_model = vertex;

    vec3 final_pos;

    if (t_period < 0.5)
    {

        float t_phase1 = t_period / 0.5;

        float mix_param = t_phase1 * t_phase1;

        final_pos = mix(pos_origen, pos_model, mix_param);
    }
    else
    {

        float mix_param = (t_period - 0.5) / 3.0;

        final_pos = mix(pos_model, pos_origen, mix_param);
    }

    vec3 N_eye = normalize(normalMatrix * normal);

    frontColor = vec4(N_eye.z, N_eye.z, N_eye.z, 1.0);

    gl_Position = modelViewProjectionMatrix * vec4(final_pos, 1.0);
}
