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
    
    mat->loadShader(Shader::DefaultShader());

    return mat;
}

void Material::loadShader(Shader *shader)
{
    this->shader = shader;

    glAttachShader(program, shader->vertex);
    glAttachShader(program, shader->fragment);

    Shader::linkProgram(program);

    glDetachShader(program, shader->vertex);
    glDetachShader(program, shader->fragment);

    int numberOfUniforms;
    glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &numberOfUniforms);

    for(int i = 0; i < numberOfUniforms; i++) {
        char name[32];
        MaterialProperty prop;
        GLsizei size, length;
        glGetActiveUniform(program, i, 32, &length, &size, &prop.type, name);
        prop.location = glGetUniformLocation(program, name);

        std::string rlname = name;

        uniformLocationMap.insert({rlname, prop});
    }
}

void Material::use()
{
    glUseProgram(program);
}

void Material::uniform1(const char *name, float value)
{
    glUniform1f(getLocation(name), value);
}

void Material::uniform1(const char *name, int value)
{
    glUniform1i(getLocation(name), value);
}

void Material::uniform1(const char *name, GLuint value)
{
    glUniform1ui(getLocation(name), value);
}

void Material::uniform1(const char *name, double value)
{
    glUniform1d(getLocation(name), value);
}

void Material::uniform3(const char *name, glm::vec3 vector)
{
    glUniform3fv(getLocation(name), 1, (float*)&vector);
}

void Material::uniform4x4(const char *name, glm::mat4 matrix)
{
    glUniformMatrix4fv(getLocation(name), 1, true, (float*)&matrix);
}

GLuint Material::getLocation(const char* name) {
    return uniformLocationMap[name].location;
}
