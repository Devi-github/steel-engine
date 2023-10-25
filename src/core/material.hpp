#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <map>
#include <string>
#include <bits/stdc++.h>

#include "shader.hpp"

struct MaterialProperty {
    GLenum type;
    GLuint location;
    char name[32];
};

class Material {
public:
    Material();
    Material(const Material& other) = delete;
    ~Material();

    static Material* Default();

    void loadShader(Shader* shader);

    GLuint getLocation(const char* name);

    void use();

    Shader* shader;
public: // TODO: Add more material shader uniform setters

    void uniform1(const char* name, float value);
    void uniform1(const char* name, int value);
    void uniform1(const char* name, GLuint value);
    void uniform1(const char* name, double value);

    void uniform3(const char* name, glm::vec3 vector);

    void uniform4x4(const char* name, glm::mat4 matrix);

private:
    std::map<std::string, MaterialProperty> uniformLocationMap;
    GLuint program;
};
