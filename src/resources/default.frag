#version 330 core

uniform vec3 lightDirection;
uniform vec3 lightColor;
uniform float lightIntensity;
uniform vec3 ambient;
uniform float ambientStrength;
uniform vec3 objectColor;
uniform float specularSmoothness;

in vec3 normal;
in vec2 texCoords;
in vec3 fragPos;

out vec4 fragColor;

void main() {
    float diff = max(dot(normal, -lightDirection), 0.0);
    vec3 result = lightColor * diff * objectColor + ambient * ambientStrength;
    fragColor = vec4(result, 1);
}
