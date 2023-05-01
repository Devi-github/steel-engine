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

void Material::uniform1(const char *name, float value)
{
    use();
    glUniform1f(getLocation(name), value);
}

void Material::uniform1(const char *name, int value)
{
    use();
    glUniform1i(getLocation(name), value);
}

void Material::uniform1(const char *name, GLuint value)
{
    use();
    glUniform1ui(getLocation(name), value);
}

void Material::uniform1(const char *name, double value)
{
    use();
    glUniform1d(getLocation(name), value);
}

void Material::uniform3(const char *name, glm::vec3 vector)
{
    use();
    glUniform3fv(getLocation(name), 1, (float*)&vector);
}

void Material::uniform4x4(const char *name, glm::mat4 matrix)
{
    use();
    glUniformMatrix4fv(getLocation(name), 1, true, (float*)&matrix);
}

GLuint Material::getLocation(const char* name) {
    return uniformLocationMap[name].location;
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
