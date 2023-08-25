#pragma once
#include <GL/glew.h>

#include <vector>

typedef unsigned char Byte;

class Shader {
public:
    Shader();
    ~Shader();

    void loadShaders(const char* vertex, const char* fragment);
    void loadShaderBinaries(std::vector<Byte> &vertex, std::vector<Byte> &fragment);

    void loadShaderFromFile(const char* vxPath, const char* fgPath);
    void loadShaderFromBinary(const char* vxBin, const char* fgBin);

    void compileShader(GLuint);
    
    static Shader* DefaultShader();
    static void linkProgram(GLuint);

    GLuint vertex, fragment;
};
