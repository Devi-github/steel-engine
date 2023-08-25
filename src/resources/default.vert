#version 330 core

layout (location = 0) in vec3 vertexPos;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec2 uv;

uniform mat4 model, view, projection, normalMatrix;

out vec3 normal;
out vec2 texCoords;
out vec3 fragPos;

void main() {
    gl_Position = vec4(vertexPos, 1) * model * view * projection;
    normal = (inverse(normalMatrix) * vec4(vertexNormal, 1)).xyz;
    texCoords = uv;
    fragPos = vertexPos;
}
