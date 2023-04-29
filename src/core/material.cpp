#include "material.hpp"
#include <iostream>

Material::Material()
{
    program = glCreateProgram();
}

Material::~Material() {
    glUseProgram(0);
    glDeleteProgram(program);
}

Material* Material::Default() {
    auto mat = new Material();
    
    mat->loadShaders(DefaultVertex, DefaultFragment);

    return mat;
}

void Material::use()
{
    glUseProgram(program);
}

void Material::loadShaders(const char *vertex, const char *fragment)
{
    GLuint vx = glCreateShader(GL_VERTEX_SHADER);
    GLuint fg = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vx, 1, &vertex, nullptr);
    compileShader(vx);

    glShaderSource(fg, 1, &fragment, nullptr);
    compileShader(fg);

    glAttachShader(program, vx);
    glAttachShader(program, fg);

    linkProgram(program);

    glDetachShader(program, vx);
    glDetachShader(program, fg);
    glDeleteShader(vx);
    glDeleteShader(fg);
}

void Material::uniform4x4(const char* name, glm::mat4 matrix) {
    glUniformMatrix4fv(getLocation(name), 1, true, (float*)&matrix);
}

GLuint Material::getLocation(const char* name) {
    return glGetUniformLocation(program, name);
}

// TODO: Add error checking
void Material::compileShader(GLuint shader) {
    glCompileShader(shader);

    int success;
    char infoLog[512];

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if(!success) {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "Error compiling shader (" << shader << ")\n\n" << infoLog << std::endl;
    }
}

// TODO: Add error checking
void Material::linkProgram(GLuint program) {
    glLinkProgram(program);

    int success;
    char infoLog[512];

    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if(!success) {
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        std::cerr << "Error linking program (" << program << ")\n\n" << infoLog << std::endl;
    }
}
