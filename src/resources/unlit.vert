#version 330 core

layout (location = 0) in vec3 vertexPos;

uniform mat4 model, view, projection;

out vec3 fragPos;

void main() {
    gl_Position = vec4(vertexPos, 1) * model * view * projection;
    fragPos = vertexPos;
}
