#pragma once
#include <GL/glew.h>

#define DefaultVertex "#version 330\n\
layout (location = 0) in vec3 vertexPos;\n\
layout (location = 1) in vec3 vertexNormal;\n\
layout (location = 2) in vec2 uv;\n\
out vec3 normal;\n\
out vec2 texCoords;\n\
void main() {\n\
    gl_Position = vec4(vertexPos, 1);\n\
    normal = vertexNormal;\n\
    texCoords = uv;\n\
}\n"
#define DefaultFragment "#version 330\n\
in vec3 normal;\n\
in vec2 texCoords;\n\
out vec4 fragColor;\n\
void main() {\n \
    fragColor = vec4(1, 0, 1, 1);\n\
}\n"

class Material {
public:
    Material();
    ~Material();

    static Material* Default();

    void use();
    void loadShaders(const char* vertex, const char* fragment);
private:

    void compileShader(GLuint);
    void linkProgram(GLuint);

    GLuint program;
};
