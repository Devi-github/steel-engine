#include "shader.hpp"

#include <iostream>
#include <string>
#include <fstream>
#include <iterator>

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

void Shader::loadShaderBinaries(std::vector<Byte> &vertex, std::vector<Byte> &fragment)
{
    GLuint vx = glCreateShader(GL_VERTEX_SHADER);
    GLuint fg = glCreateShader(GL_FRAGMENT_SHADER);

    this->vertex = vx;
    this->fragment = fg;

    glShaderBinary(1, &vx, GL_SPIR_V_BINARY, vertex.data(), vertex.size() * sizeof(Byte));
    glSpecializeShader(vx, "main", 0, 0, 0);

    glShaderBinary(1, &fg, GL_SPIR_V_BINARY, fragment.data(), fragment.size() * sizeof(Byte));
    glSpecializeShader(fg, "main", 0, 0, 0);

    // That should be all
}

std::string readFromFile(std::string path) {
    using namespace std;

    ifstream shaderFile(path, ios::in);

    if(!shaderFile.is_open()) {
        std::cerr << "Could not read file " << path << ". File doesn't exist!";
        return "";
    }

    string result;
    string line;

    while(!shaderFile.eof()) {
        std::getline(shaderFile, line);
        result.append(line + "\n");
    }

    shaderFile.close();

    return result;
}

std::vector<Byte> loadBinaryFile(const char* path) {
    using namespace std;

    ifstream file(path, ios::binary);

    file.unsetf(ios::skipws);

    streampos fileSize;

    file.seekg(0, ios::end);
    fileSize = file.tellg();
    file.seekg(0, ios::beg);

    std::vector<Byte> vec;
    vec.reserve(fileSize);

    vec.insert(vec.begin(),
        istream_iterator<Byte>(file),
        istream_iterator<Byte>());
    
    return vec;
}

void Shader::loadShaderFromFile(const char *vxPath, const char *fgPath)
{
    std::string _vertex = readFromFile(vxPath);
    std::string _fragment = readFromFile(fgPath);

    loadShaders(_vertex.c_str(), _fragment.c_str());
}

void Shader::loadShaderFromBinary(const char* vxBin, const char* fgBin) {
    std::vector<Byte> vertexBinary = loadBinaryFile(vxBin);
    std::vector<Byte> fragmentBinary = loadBinaryFile(fgBin);

    loadShaderBinaries(vertexBinary, fragmentBinary);
}

Shader *Shader::DefaultShader()
{
    if(defshad != nullptr) return defshad;

    defshad = new Shader();
    defshad->loadShaderFromFile("resources/default.vert", "resources/default.frag");
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