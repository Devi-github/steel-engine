#pragma once
#include <GL/glew.h>

#define DefaultVertex "#version 330\n\
layout (location = 0) in vec3 vertexPos;\n\
layout (location = 1) in vec3 vertexNormal;\n\
layout (location = 2) in vec2 uv;\n\
uniform mat4 model, view, projection, normalMatrix;\n\
out vec3 normal;\n\
out vec2 texCoords;\n\
out vec3 fragPos;\n\
void main() {\n\
    gl_Position = vec4(vertexPos, 1) * model * view * projection;\n\
    normal = (inverse(normalMatrix) * vec4(vertexNormal, 1)).xyz;\n\
    texCoords = uv;\n\
    fragPos = vertexPos;\n\
}\n"
#define DefaultFragment "#version 330\n\
uniform vec3 lightDirection;\n\
uniform vec3 lightColor;\n\
uniform float lightIntensity;\n\
uniform vec3 objectColor;\n\
in vec3 normal;\n\
in vec2 texCoords;\n\
in vec3 fragPos;\n\
out vec4 fragColor;\n\
void main() {\n \
    float diff = max(dot(normal, -lightDirection), 0.0);\n\
    vec3 result = lightColor * diff * objectColor;\n \
    fragColor = vec4(result, 1);\n\
}\n"

class Shader {
public:
    Shader();
    ~Shader();

    void loadShaders(const char* vertex, const char* fragment);

    void compileShader(GLuint);
    
    static Shader* DefaultShader();
    static void linkProgram(GLuint);

    GLuint vertex, fragment;
};
