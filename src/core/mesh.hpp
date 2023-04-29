#pragma once
#include <GL/glew.h>
#include "component.hpp"
#include "material.hpp"

struct Mesh {
public:
    Mesh();
    Mesh(float* buffer, GLuint* indbuff, int vxCount);
    ~Mesh();

    float* vertexBuffer;
    int vertexCount;
    int vertexSize;
    GLuint* indices;
};

class MeshRenderer : public BaseComponent {
public:
    MeshRenderer();
    ~MeshRenderer();

    void setMesh(Mesh* mesh);
    void onUpdate() override;
    void draw(GLenum primitiveType);

    Material* material;
    
private:
    Mesh* mesh;
    GLuint vbo, vao, ebo;
};
