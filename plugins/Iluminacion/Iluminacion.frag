#version 330 core

in vec3 v_vertex;
in vec3 v_normal;

out vec4 fragColor;

uniform vec4 lightPosition;
uniform vec4 lightAmbient;
uniform vec4 lightDiffuse;
uniform vec4 lightSpecular;

uniform vec4 matAmbient;
uniform vec4 matDiffuse;
uniform vec4 matSpecular;
uniform float matShininess;

void main() {

    vec3 N = normalize(v_normal);

    vec3 L = normalize(lightPosition.xyz - v_vertex);

    vec3 V = normalize(-v_vertex);

    vec3 R = reflect(-L, N);

    vec4 ambient = lightAmbient * matAmbient;

    float NdotL = max(dot(N, L), 0.0);
    vec4 diffuse = lightDiffuse * matDiffuse * NdotL;

    float RdotV = max(dot(R, V), 0.0);
    float specFactor = 0.0;

    if (NdotL > 0.0) {
        specFactor = pow(RdotV, matShininess);
    }
    vec4 specular = lightSpecular * matSpecular * specFactor;

    fragColor = ambient + diffuse + specular;
}
