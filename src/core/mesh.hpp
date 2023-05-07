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

    float* vertexBuffer;
    int vertexCount;
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
    
    Material* sharedMaterial = nullptr;

    int drawType = GL_TRIANGLES;
    
    Mesh* mesh;
public: // FIXME: Revert to private after debugging
    GLuint vbo, vao, ebo;
};
