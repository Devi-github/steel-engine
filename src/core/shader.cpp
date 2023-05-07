#include "shader.hpp"
#include <iostream>

Shader* defshad = nullptr;

Shader::Shader()
{
    vertex = -1;
    fragment = -1;
}

Shader::~Shader()
{
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::loadShaders(const char *vertex, const char *fragment)
{
    GLuint vx = glCreateShader(GL_VERTEX_SHADER);
    GLuint fg = glCreateShader(GL_FRAGMENT_SHADER);

    this->vertex = vx;
    this->fragment = fg;

    glShaderSource(vx, 1, &vertex, nullptr);
    compileShader(vx);

    glShaderSource(fg, 1, &fragment, nullptr);
    compileShader(fg);
}

Shader *Shader::DefaultShader()
{
    if(defshad != nullptr) return defshad;

    defshad = new Shader();
    defshad->loadShaders(DefaultVertex, DefaultFragment);
    return defshad;
}

// TODO: Add error checking
void Shader::linkProgram(GLuint program) {
    glLinkProgram(program);

    int success;
    char infoLog[512];

    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if(!success) {
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        std::cerr << "Error linking program (" << program << ")\n\n" << infoLog << std::endl;
    }
}

// TODO: Add error checking
void Shader::compileShader(GLuint shader) {
    glCompileShader(shader);

    int success;
    char infoLog[512];

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if(!success) {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "Error compiling shader (" << shader << ")\n\n" << infoLog << std::endl;
    }
}