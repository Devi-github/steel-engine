#pragma once
#include <GL/glew.h>
#include "component.hpp"
#include "material.hpp"

#define VERTEX_SIZE 8

struct Mesh {
public:
    Mesh();
    Mesh(float* buffer, GLuint* indbuff, int vxCount);
    Mesh(const Mesh&);
    ~Mesh();

    GLuint vbo, vao, ebo;

    float* vertexBuffer;
    int vertexCount;
    int trisCount;
    int vertexSize;
    GLuint* indices;
};

class MeshRenderer : public BaseComponent {
public:
    MeshRenderer();
    MeshRenderer(const MeshRenderer&);
    ~MeshRenderer();

    void setMesh(Mesh* mesh);
    void onUpdate() override;
    void draw(GLenum primitiveType);
    
    Material* material = nullptr;
    Material* sharedMaterial = nullptr;

    int drawType = GL_TRIANGLES;
    bool drawOutline = false;
    
    Mesh* mesh;
private:
};
