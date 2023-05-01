#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <map>
#include <string>
#include <bits/stdc++.h>

#define DefaultVertex "#version 330\n\
layout (location = 0) in vec3 vertexPos;\n\
layout (location = 1) in vec3 vertexNormal;\n\
layout (location = 2) in vec2 uv;\n\
uniform mat4 model, view, projection;\n\
out vec3 normal;\n\
out vec2 texCoords;\n\
out vec3 fragPos;\n\
void main() {\n\
    gl_Position = vec4(vertexPos, 1) * model * view * projection;\n\
    normal = mat3(inverse(model)) * vertexNormal;\n\
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

struct MaterialProperty {
    GLenum type;
    GLuint location;
};

class Material {
public:
    Material();
    ~Material();

    static Material* Default();

    void use();
    void loadShaders(const char* vertex, const char* fragment);
public: // TODO: Add more material shader uniform setters

    void uniform1(const char* name, float value);
    void uniform1(const char* name, int value);
    void uniform1(const char* name, GLuint value);
    void uniform1(const char* name, double value);

    void uniform3(const char* name, glm::vec3 vector);

    void uniform4x4(const char* name, glm::mat4 matrix);

    std::map<std::string, MaterialProperty> uniformLocationMap;

private:

    GLuint getLocation(const char* name);

    void compileShader(GLuint);
    void linkProgram(GLuint);

    GLuint program;
};
